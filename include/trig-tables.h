#ifndef TRIG_TABLES_H
#define TRIG_TABLES_H

const int sinTable[512] = {
	0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 
	48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 89, 92, 
	95, 98, 101, 104, 106, 109, 112, 115, 117, 120, 123, 125, 128, 131, 133, 136, 
	138, 141, 143, 146, 148, 151, 153, 156, 158, 160, 163, 165, 167, 170, 172, 174, 
	176, 178, 181, 183, 185, 187, 189, 191, 193, 195, 197, 198, 200, 202, 204, 206, 
	207, 209, 211, 212, 214, 215, 217, 219, 220, 221, 223, 224, 225, 227, 228, 229, 
	230, 232, 233, 234, 235, 236, 237, 238, 239, 240, 240, 241, 242, 243, 243, 244, 
	245, 245, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249, 249, 249, 249, 249, 
	250, 249, 249, 249, 249, 249, 249, 249, 248, 248, 248, 247, 247, 246, 246, 245, 
	245, 244, 243, 243, 242, 241, 240, 240, 239, 238, 237, 236, 235, 234, 233, 232, 
	230, 229, 228, 227, 225, 224, 223, 221, 220, 219, 217, 215, 214, 212, 211, 209, 
	207, 206, 204, 202, 200, 198, 197, 195, 193, 191, 189, 187, 185, 183, 181, 178, 
	176, 174, 172, 170, 167, 165, 163, 160, 158, 156, 153, 151, 148, 146, 143, 141, 
	138, 136, 133, 131, 128, 125, 123, 120, 117, 115, 112, 109, 106, 104, 101, 98, 
	95, 92, 89, 87, 84, 81, 78, 75, 72, 69, 66, 63, 60, 57, 54, 51, 
	48, 45, 42, 39, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
	0, -3, -6, -9, -12, -15, -18, -21, -24, -27, -30, -33, -36, -39, -42, -45, 
	-48, -51, -54, -57, -60, -63, -66, -69, -72, -75, -78, -81, -84, -87, -89, -92, 
	-95, -98, -101, -104, -106, -109, -112, -115, -117, -120, -123, -125, -128, -131, -133, -136, 
	-138, -141, -143, -146, -148, -151, -153, -156, -158, -160, -163, -165, -167, -170, -172, -174, 
	-176, -178, -181, -183, -185, -187, -189, -191, -193, -195, -197, -198, -200, -202, -204, -206, 
	-207, -209, -211, -212, -214, -215, -217, -219, -220, -221, -223, -224, -225, -227, -228, -229, 
	-230, -232, -233, -234, -235, -236, -237, -238, -239, -240, -240, -241, -242, -243, -243, -244, 
	-245, -245, -246, -246, -247, -247, -248, -248, -248, -249, -249, -249, -249, -249, -249, -249, 
	-250, -249, -249, -249, -249, -249, -249, -249, -248, -248, -248, -247, -247, -246, -246, -245, 
	-245, -244, -243, -243, -242, -241, -240, -240, -239, -238, -237, -236, -235, -234, -233, -232, 
	-230, -229, -228, -227, -225, -224, -223, -221, -220, -219, -217, -215, -214, -212, -211, -209, 
	-207, -206, -204, -202, -200, -198, -197, -195, -193, -191, -189, -187, -185, -183, -181, -178, 
	-176, -174, -172, -170, -167, -165, -163, -160, -158, -156, -153, -151, -148, -146, -143, -141, 
	-138, -136, -133, -131, -128, -125, -123, -120, -117, -115, -112, -109, -106, -104, -101, -98, 
	-95, -92, -89, -87, -84, -81, -78, -75, -72, -69, -66, -63, -60, -57, -54, -51, 
	-48, -45, -42, -39, -36, -33, -30, -27, -24, -21, -18, -15, -12, -9, -6, -3, 
};

const int cosTable[512] = {
	250, 249, 249, 249, 249, 249, 249, 249, 248, 248, 248, 247, 247, 246, 246, 245, 
	245, 244, 243, 243, 242, 241, 240, 240, 239, 238, 237, 236, 235, 234, 233, 232, 
	230, 229, 228, 227, 225, 224, 223, 221, 220, 219, 217, 215, 214, 212, 211, 209, 
	207, 206, 204, 202, 200, 198, 197, 195, 193, 191, 189, 187, 185, 183, 181, 178, 
	176, 174, 172, 170, 167, 165, 163, 160, 158, 156, 153, 151, 148, 146, 143, 141, 
	138, 136, 133, 131, 128, 125, 123, 120, 117, 115, 112, 109, 106, 104, 101, 98, 
	95, 92, 89, 87, 84, 81, 78, 75, 72, 69, 66, 63, 60, 57, 54, 51, 
	48, 45, 42, 39, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 
	0, -3, -6, -9, -12, -15, -18, -21, -24, -27, -30, -33, -36, -39, -42, -45, 
	-48, -51, -54, -57, -60, -63, -66, -69, -72, -75, -78, -81, -84, -87, -89, -92, 
	-95, -98, -101, -104, -106, -109, -112, -115, -117, -120, -123, -125, -128, -131, -133, -136, 
	-138, -141, -143, -146, -148, -151, -153, -156, -158, -160, -163, -165, -167, -170, -172, -174, 
	-176, -178, -181, -183, -185, -187, -189, -191, -193, -195, -197, -198, -200, -202, -204, -206, 
	-207, -209, -211, -212, -214, -215, -217, -219, -220, -221, -223, -224, -225, -227, -228, -229, 
	-230, -232, -233, -234, -235, -236, -237, -238, -239, -240, -240, -241, -242, -243, -243, -244, 
	-245, -245, -246, -246, -247, -247, -248, -248, -248, -249, -249, -249, -249, -249, -249, -249, 
	-250, -249, -249, -249, -249, -249, -249, -249, -248, -248, -248, -247, -247, -246, -246, -245, 
	-245, -244, -243, -243, -242, -241, -240, -240, -239, -238, -237, -236, -235, -234, -233, -232, 
	-230, -229, -228, -227, -225, -224, -223, -221, -220, -219, -217, -215, -214, -212, -211, -209, 
	-207, -206, -204, -202, -200, -198, -197, -195, -193, -191, -189, -187, -185, -183, -181, -178, 
	-176, -174, -172, -170, -167, -165, -163, -160, -158, -156, -153, -151, -148, -146, -143, -141, 
	-138, -136, -133, -131, -128, -125, -123, -120, -117, -115, -112, -109, -106, -104, -101, -98, 
	-95, -92, -89, -87, -84, -81, -78, -75, -72, -69, -66, -63, -60, -57, -54, -51, 
	-48, -45, -42, -39, -36, -33, -30, -27, -24, -21, -18, -15, -12, -9, -6, -3, 
	0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 
	48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 89, 92, 
	95, 98, 101, 104, 106, 109, 112, 115, 117, 120, 123, 125, 128, 131, 133, 136, 
	138, 141, 143, 146, 148, 151, 153, 156, 158, 160, 163, 165, 167, 170, 172, 174, 
	176, 178, 181, 183, 185, 187, 189, 191, 193, 195, 197, 198, 200, 202, 204, 206, 
	207, 209, 211, 212, 214, 215, 217, 219, 220, 221, 223, 224, 225, 227, 228, 229, 
	230, 232, 233, 234, 235, 236, 237, 238, 239, 240, 240, 241, 242, 243, 243, 244, 
	245, 245, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249, 249, 249, 249, 249, 
};

#endif