#include <stdio.h>
#include <math.h>
#include <string.h>
#include <czmq.h>

#include "../libs/rtklib-2.4.3/src/rtklib.h"

#include "../include/main.h"
#include "../include/simulator.h"

#define GPS_SV_COUNT 32

FILE *OutputFile;
zsock_t* OutputSocket;

eph_t Ephemerides[GPS_SV_COUNT];

void dumpFile(short* buffer, int length) {
    fwrite(buffer, sizeof(buffer[0]), length, OutputFile);
}

void dumpSocket(short* buffer, int length) {
    zsock_send(OutputSocket, "b", buffer, (length * sizeof(short)));
    zclock_sleep(10);
}

static int compareEphemerides(const void *p1, const void *p2) {
    eph_t *q1 = (eph_t *)p1;
    eph_t *q2 = (eph_t *)p2;
    
    // Compare based on satellite ID and time of ephemeris
    if (q1->sat != q2->sat) {
        return q1->sat - q2->sat;
    }

    // Sort in descending order of time
    else {
        return q2->toe.time - q1->toe.time;
    }
}

void saveEphemerides(eph_t* ephemerides) {
    FILE *fp;

    fp = fopen("gnss-sim-ephemeris.txt", "w+");
    
    // NOTE: SVs transmit some values in "semicircles". Our supplied RINEX file presents these values
    //       in radians (part of the RINEX spec). These are converted to semicircles later. They are
    //       displayed in radians here so that they can be compared with the "gps_ephemeris.xml"
    //       generated by GNSS-SDR for debugging.
    fprintf(fp, "PRN: %i\n", ephemerides[0].sat);
    fprintf(fp, "M_0: %.17e\n", ephemerides[0].M0);
    fprintf(fp, "delta_n: %.17e\n", ephemerides[0].deln);
    fprintf(fp, "ecc: %.17e\n", ephemerides[0].e);
    fprintf(fp, "sqrtA: %.17e\n", sqrt(ephemerides[0].A));
    fprintf(fp, "OMEGA_0: %.17e\n", ephemerides[0].OMG0);
    fprintf(fp, "i_0: %.17e\n", ephemerides[0].i0);
    fprintf(fp, "omega: %.17e\n", ephemerides[0].omg);
    fprintf(fp, "OMEGAdot: %.17e\n", ephemerides[0].OMGd);
    fprintf(fp, "idot: %.17e\n", ephemerides[0].idot);
    fprintf(fp, "Cuc: %.17e\n", ephemerides[0].cuc);
    fprintf(fp, "Cus: %.17e\n", ephemerides[0].cus);
    fprintf(fp, "Crc: %.17e\n", ephemerides[0].crc);
    fprintf(fp, "Crs: %.17e\n", ephemerides[0].crs);
    fprintf(fp, "Cic: %.17e\n", ephemerides[0].cic);
    fprintf(fp, "Cis: %.17e\n", ephemerides[0].cis);
    fprintf(fp, "toe: %i\n", (unsigned long)time2gpst(ephemerides[0].toe, NULL));
    fprintf(fp, "toc: %i\n", (unsigned long)time2gpst(ephemerides[0].toc, NULL));
    fprintf(fp, "af0: %.17e\n", ephemerides[0].f0);
    fprintf(fp, "af1: %.17e\n", ephemerides[0].f1);
    fprintf(fp, "af2: %.17e\n", ephemerides[0].f2);

    // The value transmitted is the modulo 1024 of the actual week number.
    // Need to perform this modulo (using bitmask) if we want to compare values.
    fprintf(fp, "WN: %i\n", (ephemerides[0].week & BITMASK(10)));

    fprintf(fp, "SV_accuracy: %i\n", ephemerides[0].sva);
    fprintf(fp, "SV_health: %i\n", ephemerides[0].svh);
    fprintf(fp, "TGD: %.17e\n", ephemerides[0].tgd[0]);
    fprintf(fp, "IODC: %i\n", ephemerides[0].iodc);

    fclose(fp);
}

int loadEphemerides(char* filename, eph_t* ephemerides) {
    // Only interested in GPS ephemerides for now
    char* opt = "-SYS=G";

    // Dummy variable to store navigation data initially
    nav_t nav = {0};

    // Open ephemerides file
    if (!readrnx(filename, NULL, opt, NULL, &nav, NULL)) {
        printf("Error: Could not open ephemerides file\n");
        return -1;
    }

    // Sort the array based on satellite ID and time of ephemeris
    qsort(nav.eph, nav.n, sizeof(eph_t), compareEphemerides);

    // Declare iterators
    int i, j;
    
    // Iterate through the array to keep only the most recent ephemeris for each satellite ID
    for (i = 0, j = 1; j < nav.n; j++) {
        if (nav.eph[j].sat != nav.eph[i].sat) {
            // Move to the next satellite ID
            i++;

            // Keep the most recent ephemeris for this satellite ID
            nav.eph[i] = nav.eph[j];
        }
    }

    // Copy out of nav
    short count = (i + 1);
    memcpy(ephemerides, nav.eph, (count * sizeof(eph_t)));

    // Display result!
    printf("GPS EPHEMERIDES LOADED: %i\n", count);

    // Uncomment for debugging
    saveEphemerides(ephemerides);

    return 0;
}

void showHelp() {
    printf("Usage: program_name [options]\n");
    printf("Options:\n");
    printf("  -h\t\tShow this help message\n");
    printf("  -e <file>\tSet the ephemerides file. Required!\n");
    printf("  -o <file>\tSet the output file. If no file specified, output will be streamed on ZMQ TCP 5555\n");
}

int main(int argc, char *argv[]) {
    void (*filePtr)(short*, int) = &dumpFile;
    void (*socketPtr)(short*, int) = &dumpSocket;

    char *ephemeridesFilename = NULL;
    char *outputFilename = NULL;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            showHelp();
            return 0;
        }

        else if (strcmp(argv[i], "-e") == 0) {
            if (i + 1 < argc) {
                ephemeridesFilename = argv[i + 1];

                // Skip the next argument as it is the filename
                i++;
            }
            
            else {
                printf("Error: -e flag requires a filename argument\n");
                return 1;
            }
        }
        
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                outputFilename = argv[i + 1];

                // Skip the next argument as it is the filename
                i++;
            }
            
            else {
                printf("Error: -o flag requires a filename argument\n");
                return 1;
            }
        }
        
        else {
            printf("Error: Unknown option '%s'\n", argv[i]);
            return 1;
        }
    }

    if (!ephemeridesFilename) {
        printf("Error: ephemerides must be provided. See help\n");
        return 0;
    }

    loadEphemerides(ephemeridesFilename, Ephemerides);

    // Enter file mode if output file specified
    if (outputFilename) {
        printf("WRITING DATA TO FILE...\n");
        OutputFile = fopen(outputFilename, "wb");
        simulate(filePtr, Ephemerides);
        fclose(OutputFile);
    }

    // Otherwise, enter streaming mode
    else {
        printf("STREAMING DATA...\n");
        OutputSocket = zsock_new_pub("tcp://127.0.0.1:5555");

        // Sleep to give subscriber time to connect
        sleep(1);

        simulate(socketPtr, Ephemerides);

        // Sleep to give subscriber time to collect
        sleep(1);

        zsock_destroy(&OutputSocket);
    }

    return 0;
}