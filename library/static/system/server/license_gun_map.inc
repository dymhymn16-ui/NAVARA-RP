static CreateDynamicObjectCustom(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, areaid = -1, priority = 0)
{
	interiorid = LICENSE_GUN_SHOP_INTERIOR;
	worldid = LICENSE_GUN_SHOP_WORLD;
	return CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance, areaid, priority);
}

LoadLicenseGunShopMap()
{
	new g_Object[218];
	g_Object[0] = CreateDynamicObjectCustom(1271, -1727.3221, 77.5911, 3.0104, 0.0000, 0.0000, 47.2000); //gunbox
	g_Object[1] = CreateDynamicObjectCustom(19378, -1722.0107, 76.8125, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	SetDynamicObjectMaterial(g_Object[1], 0, 14668, "711c", "gun_ceiling1128", 0x00000000);
	g_Object[2] = CreateDynamicObjectCustom(19368, -1727.9964, 75.1781, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[2], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[3] = CreateDynamicObjectCustom(19378, -1715.0422, 70.1976, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	SetDynamicObjectMaterial(g_Object[3], 0, 14668, "711c", "gun_ceiling1128", 0x00000000);
	g_Object[4] = CreateDynamicObjectCustom(19378, -1707.8360, 77.7926, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	SetDynamicObjectMaterial(g_Object[4], 0, 14668, "711c", "gun_ceiling1128", 0x00000000);
	g_Object[5] = CreateDynamicObjectCustom(19378, -1714.7978, 84.4147, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	SetDynamicObjectMaterial(g_Object[5], 0, 14668, "711c", "gun_ceiling1128", 0x00000000);
	g_Object[6] = CreateDynamicObjectCustom(19364, -1728.0797, 77.5251, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[6], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[7] = CreateDynamicObjectCustom(19378, -1722.0107, 76.8125, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	g_Object[8] = CreateDynamicObjectCustom(19364, -1725.8878, 79.8283, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[8], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[9] = CreateDynamicObjectCustom(19364, -1723.7042, 82.1240, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[9], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[10] = CreateDynamicObjectCustom(19364, -1721.5664, 84.3691, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[10], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[11] = CreateDynamicObjectCustom(19364, -1719.3929, 86.6501, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[11], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[12] = CreateDynamicObjectCustom(19364, -1717.2170, 88.9384, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[12], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[13] = CreateDynamicObjectCustom(19364, -1715.8032, 90.4231, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[13], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[14] = CreateDynamicObjectCustom(19364, -1715.8248, 90.4438, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[14], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[15] = CreateDynamicObjectCustom(19364, -1718.0028, 88.1555, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[15], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[16] = CreateDynamicObjectCustom(19364, -1720.2131, 85.8309, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[16], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[17] = CreateDynamicObjectCustom(19364, -1722.4189, 83.5130, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[17], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[18] = CreateDynamicObjectCustom(19364, -1724.6312, 81.1890, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[18], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[19] = CreateDynamicObjectCustom(19364, -1726.8382, 78.8712, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[19], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[20] = CreateDynamicObjectCustom(19364, -1728.0826, 77.5680, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[20], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[21] = CreateDynamicObjectCustom(19368, -1725.7086, 72.9841, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[21], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[22] = CreateDynamicObjectCustom(19368, -1723.3985, 70.7693, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[22], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[23] = CreateDynamicObjectCustom(19368, -1721.0968, 68.5615, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[23], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[24] = CreateDynamicObjectCustom(19368, -1718.7945, 66.3535, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[24], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[25] = CreateDynamicObjectCustom(19368, -1716.4764, 64.1315, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[25], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[26] = CreateDynamicObjectCustom(19368, -1728.0246, 75.1632, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[26], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[27] = CreateDynamicObjectCustom(19368, -1725.7231, 72.9557, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[27], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[28] = CreateDynamicObjectCustom(19368, -1723.4267, 70.7546, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[28], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[29] = CreateDynamicObjectCustom(19368, -1721.1379, 68.5605, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[29], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[30] = CreateDynamicObjectCustom(19368, -1718.8293, 66.3457, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[30], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[31] = CreateDynamicObjectCustom(19364, -1714.1745, 64.2845, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[31], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[32] = CreateDynamicObjectCustom(19364, -1710.6583, 67.9708, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[32], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[33] = CreateDynamicObjectCustom(19364, -1712.8381, 65.6819, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[33], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[34] = CreateDynamicObjectCustom(19364, -1711.9831, 66.5874, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[34], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[35] = CreateDynamicObjectCustom(19364, -1709.8199, 68.8610, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[35], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[36] = CreateDynamicObjectCustom(19364, -1707.6584, 71.1351, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[36], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[37] = CreateDynamicObjectCustom(19364, -1705.5030, 73.4017, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[37], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[38] = CreateDynamicObjectCustom(19364, -1703.2912, 75.7263, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[38], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[39] = CreateDynamicObjectCustom(19364, -1701.8999, 77.1891, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[39], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[40] = CreateDynamicObjectCustom(19364, -1704.0936, 74.8720, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[40], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[41] = CreateDynamicObjectCustom(19364, -1706.2972, 72.5547, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[41], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[42] = CreateDynamicObjectCustom(19364, -1708.4604, 70.2807, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[42], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[43] = CreateDynamicObjectCustom(19364, -1714.9105, 63.5023, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[43], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[44] = CreateDynamicObjectCustom(19364, -1728.1374, 77.5100, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[44], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[45] = CreateDynamicObjectCustom(2985, -1728.2534, 76.3507, 2.6596, 0.0000, 0.0000, 0.0000); //minigun_base
	g_Object[46] = CreateDynamicObjectCustom(2041, -1727.4868, 77.6051, 3.5604, 0.0000, 0.0000, 0.0000); //AMMO_BOX_M2
	g_Object[47] = CreateDynamicObjectCustom(1271, -1726.6623, 78.3028, 3.0104, 0.0000, 0.0000, 47.2000); //gunbox
	g_Object[48] = CreateDynamicObjectCustom(1271, -1727.3686, 75.2470, 3.0104, 0.0000, 0.0000, 47.2000); //gunbox
	g_Object[49] = CreateDynamicObjectCustom(353, -1726.3540, 78.2201, 3.3405, 82.5998, -15.8000, -125.1996); //mp5lng
	g_Object[50] = CreateDynamicObjectCustom(2041, -1726.6864, 78.4748, 3.5604, 0.0000, 0.0000, -73.3999); //AMMO_BOX_M2
	g_Object[51] = CreateDynamicObjectCustom(2358, -1726.2530, 78.9345, 2.8348, 0.0000, 0.0000, 46.1999); //AMMO_BOX_c2
	g_Object[52] = CreateDynamicObjectCustom(2358, -1726.2530, 78.9345, 3.0548, 0.0000, 0.0000, 46.1999); //AMMO_BOX_c2
	g_Object[53] = CreateDynamicObjectCustom(2359, -1725.6584, 79.6473, 2.8735, 0.0000, 0.0000, 44.2000); //AMMO_BOX_c5
	g_Object[54] = CreateDynamicObjectCustom(19922, -1723.4798, 81.1548, 2.6760, 0.0000, 0.0000, 46.3997); //MKTable1
	g_Object[55] = CreateDynamicObjectCustom(3014, -1726.8885, 74.7620, 2.8845, 0.0000, 0.0000, -41.0003); //cr_guncrate
	g_Object[56] = CreateDynamicObjectCustom(339, -1722.7541, 81.7526, 3.4818, 86.0998, 57.3997, -137.9001); //katana
	g_Object[57] = CreateDynamicObjectCustom(339, -1722.6997, 81.4177, 3.4623, 86.0998, 57.3997, -137.9001); //katana
	g_Object[58] = CreateDynamicObjectCustom(339, -1723.7501, 80.1957, 3.5160, -85.7003, 133.8997, 132.6999); //katana
	g_Object[59] = CreateDynamicObjectCustom(339, -1724.0504, 80.2023, 3.5322, -85.7003, 133.8997, 132.6999); //katana
	g_Object[60] = CreateDynamicObjectCustom(356, -1722.6081, 82.0363, 3.4690, 83.9997, -51.9000, -131.2998); //m4
	g_Object[61] = CreateDynamicObjectCustom(356, -1724.3270, 80.2667, 3.5443, -98.0000, -49.4000, 45.7999); //m4
	g_Object[62] = CreateDynamicObjectCustom(2064, -1715.3320, 64.7854, 3.2857, 0.0000, 0.0000, 179.3000); //CJ_FEILDGUN
	g_Object[63] = CreateDynamicObjectCustom(2064, -1713.5898, 66.4347, 3.2857, 0.0000, 0.0000, 179.3000); //CJ_FEILDGUN
	g_Object[64] = CreateDynamicObjectCustom(2064, -1711.9256, 68.2648, 3.2857, 0.0000, 0.0000, 179.3000); //CJ_FEILDGUN
	g_Object[65] = CreateDynamicObjectCustom(1271, -1727.3221, 77.5911, 3.0104, 0.0000, 0.0000, 47.2000); //gunbox
	g_Object[66] = CreateDynamicObjectCustom(19378, -1722.0107, 76.8125, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	g_Object[67] = CreateDynamicObjectCustom(19368, -1727.9964, 75.1781, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[67], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[68] = CreateDynamicObjectCustom(19378, -1715.0422, 70.1976, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	g_Object[69] = CreateDynamicObjectCustom(19378, -1707.8360, 77.7926, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	g_Object[70] = CreateDynamicObjectCustom(19378, -1714.7978, 84.4147, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	g_Object[71] = CreateDynamicObjectCustom(19364, -1728.0797, 77.5251, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[71], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[72] = CreateDynamicObjectCustom(19378, -1722.0107, 76.8125, 2.5745, 0.0000, 89.9999, 46.4998); //wall026
	g_Object[73] = CreateDynamicObjectCustom(19364, -1722.4189, 83.5130, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[73], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[74] = CreateDynamicObjectCustom(19364, -1724.6312, 81.1890, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[74], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[75] = CreateDynamicObjectCustom(19364, -1726.8382, 78.8712, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[75], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[76] = CreateDynamicObjectCustom(19364, -1728.0826, 77.5680, 6.2705, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[76], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[77] = CreateDynamicObjectCustom(19368, -1725.7086, 72.9841, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[77], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[78] = CreateDynamicObjectCustom(19368, -1723.3985, 70.7693, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[78], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[79] = CreateDynamicObjectCustom(19368, -1721.0968, 68.5615, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[79], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[80] = CreateDynamicObjectCustom(19368, -1718.7945, 66.3535, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[80], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[81] = CreateDynamicObjectCustom(19368, -1716.4764, 64.1315, 3.7204, 0.0000, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[81], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[82] = CreateDynamicObjectCustom(19368, -1728.0246, 75.1632, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[82], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[83] = CreateDynamicObjectCustom(19368, -1725.7231, 72.9557, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[83], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[84] = CreateDynamicObjectCustom(19368, -1723.4267, 70.7546, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[84], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[85] = CreateDynamicObjectCustom(19368, -1721.1379, 68.5605, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[85], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[86] = CreateDynamicObjectCustom(19368, -1718.8293, 66.3457, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[86], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[87] = CreateDynamicObjectCustom(19368, -1716.5649, 64.1725, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[87], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[88] = CreateDynamicObjectCustom(19364, -1714.1745, 64.2845, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[88], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[89] = CreateDynamicObjectCustom(19364, -1710.6583, 67.9708, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[89], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[90] = CreateDynamicObjectCustom(19364, -1712.8381, 65.6819, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[90], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[91] = CreateDynamicObjectCustom(19364, -1709.8199, 68.8610, 3.6605, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[91], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[92] = CreateDynamicObjectCustom(19364, -1701.8927, 77.1819, 6.2806, 0.0000, 0.0000, -43.5998); //wall012
	SetDynamicObjectMaterial(g_Object[92], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[93] = CreateDynamicObjectCustom(19368, -1716.5649, 64.1725, 6.2705, -179.9996, 0.0000, 46.1999); //wall016
	SetDynamicObjectMaterial(g_Object[93], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[94] = CreateDynamicObjectCustom(2985, -1728.2534, 76.3507, 2.6596, 0.0000, 0.0000, 0.0000); //minigun_base
	g_Object[95] = CreateDynamicObjectCustom(2041, -1727.4868, 77.6051, 3.5604, 0.0000, 0.0000, 0.0000); //AMMO_BOX_M2
	g_Object[96] = CreateDynamicObjectCustom(1271, -1726.6623, 78.3028, 3.0104, 0.0000, 0.0000, 47.2000); //gunbox
	g_Object[97] = CreateDynamicObjectCustom(1271, -1727.3686, 75.2470, 3.0104, 0.0000, 0.0000, 47.2000); //gunbox
	g_Object[98] = CreateDynamicObjectCustom(353, -1726.3540, 78.2201, 3.3405, 82.5998, -15.8000, -125.1996); //mp5lng
	g_Object[99] = CreateDynamicObjectCustom(2041, -1726.6864, 78.4748, 3.5604, 0.0000, 0.0000, -73.3999); //AMMO_BOX_M2
	g_Object[100] = CreateDynamicObjectCustom(2358, -1726.2530, 78.9345, 2.8348, 0.0000, 0.0000, 46.1999); //AMMO_BOX_c2
	g_Object[101] = CreateDynamicObjectCustom(2358, -1726.2530, 78.9345, 3.0548, 0.0000, 0.0000, 46.1999); //AMMO_BOX_c2
	g_Object[102] = CreateDynamicObjectCustom(2359, -1725.6584, 79.6473, 2.8735, 0.0000, 0.0000, 44.2000); //AMMO_BOX_c5
	g_Object[103] = CreateDynamicObjectCustom(19922, -1723.4798, 81.1548, 2.6760, 0.0000, 0.0000, 46.3997); //MKTable1
	g_Object[104] = CreateDynamicObjectCustom(3014, -1726.8885, 74.7620, 2.8845, 0.0000, 0.0000, -41.0003); //cr_guncrate
	g_Object[105] = CreateDynamicObjectCustom(339, -1722.7541, 81.7526, 3.4818, 86.0998, 57.3997, -137.9001); //katana
	g_Object[106] = CreateDynamicObjectCustom(339, -1722.6997, 81.4177, 3.4623, 86.0998, 57.3997, -137.9001); //katana
	g_Object[107] = CreateDynamicObjectCustom(339, -1723.7501, 80.1957, 3.5160, -85.7003, 133.8997, 132.6999); //katana
	g_Object[108] = CreateDynamicObjectCustom(339, -1724.0504, 80.2023, 3.5322, -85.7003, 133.8997, 132.6999); //katana
	g_Object[109] = CreateDynamicObjectCustom(356, -1722.6081, 82.0363, 3.4690, 83.9997, -51.9000, -131.2998); //m4
	g_Object[110] = CreateDynamicObjectCustom(356, -1724.3270, 80.2667, 3.5443, -98.0000, -49.4000, 45.7999); //m4
	g_Object[111] = CreateDynamicObjectCustom(2064, -1715.3320, 64.7854, 3.2857, 0.0000, 0.0000, 179.3000); //CJ_FEILDGUN
	g_Object[112] = CreateDynamicObjectCustom(2064, -1713.5898, 66.4347, 3.2857, 0.0000, 0.0000, 179.3000); //CJ_FEILDGUN
	g_Object[113] = CreateDynamicObjectCustom(2064, -1711.9256, 68.2648, 3.2857, 0.0000, 0.0000, 179.3000); //CJ_FEILDGUN
	g_Object[114] = CreateDynamicObjectCustom(2058, -1726.5876, 75.2425, 2.6705, 0.0000, 0.0000, 0.0000); //CJ_Gun_docs
	g_Object[115] = CreateDynamicObjectCustom(2060, -1710.6551, 68.9673, 2.7695, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[116] = CreateDynamicObjectCustom(2060, -1710.6551, 68.9673, 2.9795, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[117] = CreateDynamicObjectCustom(2060, -1710.6551, 68.9673, 3.1493, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[118] = CreateDynamicObjectCustom(2060, -1712.8475, 67.3675, 2.7695, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[119] = CreateDynamicObjectCustom(2060, -1712.8475, 67.3675, 3.0295, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[120] = CreateDynamicObjectCustom(2060, -1712.8475, 67.3675, 3.2795, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[121] = CreateDynamicObjectCustom(2060, -1714.5372, 65.6175, 2.7595, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[122] = CreateDynamicObjectCustom(2060, -1714.5372, 65.6175, 2.9395, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[123] = CreateDynamicObjectCustom(2060, -1714.5372, 65.6175, 3.1394, 0.0000, 0.0000, 0.0000); //CJ_SANDBAG
	g_Object[124] = CreateDynamicObjectCustom(19356, -1706.8028, 81.7228, 7.9102, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[124], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[125] = CreateDynamicObjectCustom(19356, -1713.5604, 88.2966, 7.9102, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[125], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[126] = CreateDynamicObjectCustom(19356, -1720.9978, 71.6100, 7.8206, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[126], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[127] = CreateDynamicObjectCustom(19355, -1701.9541, 79.5798, 3.6605, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[127], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[128] = CreateDynamicObjectCustom(2059, -1725.5632, 78.8507, 2.6805, 0.0000, 0.0000, 0.0000); //CJ_GUNSTUFF1
	g_Object[129] = CreateDynamicObjectCustom(2710, -1723.3895, 80.4869, 3.5803, 0.0000, 0.0000, 44.7999); //WATCH_PICKUP
	g_Object[130] = CreateDynamicObjectCustom(2710, -1723.2054, 80.6705, 3.5803, 0.0000, 0.0000, 44.7999); //WATCH_PICKUP
	g_Object[131] = CreateDynamicObjectCustom(2710, -1723.0355, 80.8395, 3.5803, 0.0000, 0.0000, 44.7999); //WATCH_PICKUP
	g_Object[132] = CreateDynamicObjectCustom(19356, -1723.2695, 73.8199, 7.8206, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[132], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[133] = CreateDynamicObjectCustom(19355, -1704.2181, 81.7826, 3.6605, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[133], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[134] = CreateDynamicObjectCustom(19355, -1704.2336, 81.8106, 6.2203, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[134], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[135] = CreateDynamicObjectCustom(19355, -1706.5998, 83.9552, 3.6605, 0.0000, 0.0000, 46.8997); //wall003
	SetDynamicObjectMaterial(g_Object[135], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[136] = CreateDynamicObjectCustom(19355, -1704.2700, 81.7751, 3.6605, 0.0000, 0.0000, 46.8997); //wall003
	SetDynamicObjectMaterial(g_Object[136], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[137] = CreateDynamicObjectCustom(19355, -1708.9416, 86.1483, 3.6605, 0.0000, 0.0000, 46.8997); //wall003
	SetDynamicObjectMaterial(g_Object[137], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[138] = CreateDynamicObjectCustom(19355, -1711.2335, 88.2938, 3.6605, 0.0000, 0.0000, 46.8997); //wall003
	SetDynamicObjectMaterial(g_Object[138], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[139] = CreateDynamicObjectCustom(19355, -1713.5354, 90.4458, 3.6605, 0.0000, 0.0000, 46.8997); //wall003
	SetDynamicObjectMaterial(g_Object[139], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[140] = CreateDynamicObjectCustom(19355, -1701.9471, 79.5867, 6.2203, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[140], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[141] = CreateDynamicObjectCustom(19355, -1706.4621, 83.9793, 6.2203, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[141], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[142] = CreateDynamicObjectCustom(19355, -1708.7424, 86.1964, 6.2203, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[142], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[143] = CreateDynamicObjectCustom(19355, -1713.3164, 90.6444, 6.2203, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[143], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[144] = CreateDynamicObjectCustom(19355, -1714.5434, 91.4617, 6.2203, 0.0000, 0.0000, 45.7999); //wall003
	SetDynamicObjectMaterial(g_Object[144], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[145] = CreateDynamicObjectCustom(19355, -1712.2458, 89.3093, 6.2203, 0.0000, 0.0000, 46.7000); //wall003
	SetDynamicObjectMaterial(g_Object[145], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[146] = CreateDynamicObjectCustom(19355, -1709.9394, 87.1351, 6.2203, 0.0000, 0.0000, 46.7000); //wall003
	SetDynamicObjectMaterial(g_Object[146], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[147] = CreateDynamicObjectCustom(19355, -1707.6402, 84.9680, 6.2203, 0.0000, 0.0000, 46.7000); //wall003
	SetDynamicObjectMaterial(g_Object[147], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[148] = CreateDynamicObjectCustom(19355, -1705.3319, 82.7938, 6.2203, 0.0000, 0.0000, 46.7000); //wall003
	SetDynamicObjectMaterial(g_Object[148], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[149] = CreateDynamicObjectCustom(19355, -1702.9969, 80.6349, 6.2203, 0.0000, 0.0000, 46.7000); //wall003
	SetDynamicObjectMaterial(g_Object[149], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[150] = CreateDynamicObjectCustom(19355, -1701.5190, 79.2425, 6.2203, 0.0000, 0.0000, 46.7000); //wall003
	SetDynamicObjectMaterial(g_Object[150], 0, 12850, "cunte_block1", "ws_ornatewall1", 0x00000000);
	g_Object[151] = CreateDynamicObjectCustom(1493, -1706.7163, 83.8694, 2.6098, 0.0, 0.0000, 137.9002); //Gen_doorSHOP01
	SetDynamicObjectMaterial(g_Object[151], 1, 18065, "ab_sfammumain", "gun_door1", 0x00000000);
	g_Object[152] = CreateDynamicObjectCustom(19356, -1718.7191, 69.3927, 7.8206, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[152], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[153] = CreateDynamicObjectCustom(19356, -1725.5483, 76.0373, 7.8206, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[153], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[154] = CreateDynamicObjectCustom(19356, -1716.4387, 67.1762, 7.8206, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[154], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[155] = CreateDynamicObjectCustom(19356, -1714.1610, 64.9589, 7.8206, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[155], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[156] = CreateDynamicObjectCustom(19356, -1716.5626, 62.4859, 7.8024, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[156], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[157] = CreateDynamicObjectCustom(19356, -1718.8050, 64.7388, 7.8028, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[157], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[158] = CreateDynamicObjectCustom(19356, -1711.7368, 67.4540, 7.8386, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[158], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[159] = CreateDynamicObjectCustom(19356, -1711.3166, 86.1147, 7.9102, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[159], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[160] = CreateDynamicObjectCustom(19356, -1709.3382, 69.9197, 7.8568, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[160], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[161] = CreateDynamicObjectCustom(19356, -1706.8988, 72.4291, 7.8751, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[161], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[162] = CreateDynamicObjectCustom(19356, -1704.5019, 74.8955, 7.8930, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[162], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[163] = CreateDynamicObjectCustom(19356, -1702.0981, 77.3684, 7.9112, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[163], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[164] = CreateDynamicObjectCustom(19356, -1701.2474, 78.2434, 7.9176, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[164], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[165] = CreateDynamicObjectCustom(19356, -1709.0675, 83.9259, 7.9102, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[165], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[166] = CreateDynamicObjectCustom(19356, -1704.4968, 79.4776, 7.9102, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[166], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[167] = CreateDynamicObjectCustom(19356, -1706.7943, 77.1119, 7.8930, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[167], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[168] = CreateDynamicObjectCustom(19356, -1709.2384, 74.5957, 7.8747, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[168], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[169] = CreateDynamicObjectCustom(19356, -1711.6429, 72.1222, 7.8565, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[169], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[170] = CreateDynamicObjectCustom(19356, -1714.0278, 69.6705, 7.8386, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[170], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[171] = CreateDynamicObjectCustom(19356, -1716.3547, 71.8375, 7.8383, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[171], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[172] = CreateDynamicObjectCustom(19356, -1718.6118, 74.0335, 7.8383, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[172], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[173] = CreateDynamicObjectCustom(19356, -1715.8540, 90.5279, 7.9102, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[173], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[174] = CreateDynamicObjectCustom(19356, -1718.2795, 88.0332, 7.8920, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[174], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[175] = CreateDynamicObjectCustom(19356, -1720.6009, 85.6455, 7.8747, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[175], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[176] = CreateDynamicObjectCustom(19356, -1723.0124, 83.1651, 7.8565, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[176], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[177] = CreateDynamicObjectCustom(19356, -1725.3868, 80.7207, 7.8386, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[177], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[178] = CreateDynamicObjectCustom(19356, -1727.7845, 78.2546, 7.8207, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[178], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[179] = CreateDynamicObjectCustom(19356, -1730.2154, 75.7526, 7.8024, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[179], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[180] = CreateDynamicObjectCustom(19356, -1727.9571, 73.5565, 7.8024, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[180], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[181] = CreateDynamicObjectCustom(19356, -1725.6645, 71.3255, 7.8024, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[181], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[182] = CreateDynamicObjectCustom(19356, -1723.3935, 69.1156, 7.8024, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[182], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[183] = CreateDynamicObjectCustom(19356, -1721.1297, 66.9123, 7.8024, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[183], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[184] = CreateDynamicObjectCustom(19356, -1720.8974, 76.2574, 7.8383, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[184], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[185] = CreateDynamicObjectCustom(19356, -1723.1684, 78.4251, 7.8382, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[185], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[186] = CreateDynamicObjectCustom(19356, -1720.7441, 80.8916, 7.8562, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[186], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[187] = CreateDynamicObjectCustom(19356, -1718.4095, 83.2929, 7.8737, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[187], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[188] = CreateDynamicObjectCustom(19356, -1715.9719, 85.8022, 7.8920, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[188], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[189] = CreateDynamicObjectCustom(19356, -1713.7296, 83.6203, 7.8920, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[189], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[190] = CreateDynamicObjectCustom(19356, -1711.5152, 81.4661, 7.8920, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[190], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[191] = CreateDynamicObjectCustom(19356, -1709.0898, 79.3998, 7.8733, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[191], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[192] = CreateDynamicObjectCustom(19356, -1708.7524, 79.0718, 7.8733, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[192], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[193] = CreateDynamicObjectCustom(19356, -1716.1529, 81.1819, 7.8741, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[193], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[194] = CreateDynamicObjectCustom(19356, -1718.5301, 78.7369, 7.8562, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[194], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[195] = CreateDynamicObjectCustom(19356, -1716.2635, 76.5342, 7.8562, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[195], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[196] = CreateDynamicObjectCustom(19356, -1713.9758, 74.3102, 7.8562, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[196], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[197] = CreateDynamicObjectCustom(19356, -1711.5504, 76.8050, 7.8744, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[197], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[198] = CreateDynamicObjectCustom(19356, -1713.1573, 78.6071, 7.8754, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[198], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[199] = CreateDynamicObjectCustom(19356, -1713.4079, 78.3488, 7.8734, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[199], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[200] = CreateDynamicObjectCustom(19356, -1711.1252, 77.2136, 7.8776, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[200], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[201] = CreateDynamicObjectCustom(19356, -1713.5046, 79.5288, 7.8776, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[201], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[202] = CreateDynamicObjectCustom(19356, -1714.1030, 78.9122, 7.8730, 179.9996, 90.2994, 45.7999); //wall004
	SetDynamicObjectMaterial(g_Object[202], 0, 10101, "2notherbuildsfe", "sl_vicwall02", 0x00000000);
	g_Object[203] = CreateDynamicObjectCustom(19922, -1721.6832, 71.8320, 2.7060, 0.0000, 0.0000, -44.8997); //MKTable1
	g_Object[204] = CreateDynamicObjectCustom(2229, -1714.4527, 90.9822, 2.6605, 0.0000, 0.0000, 2.4999); //SWANK_SPEAKER
	g_Object[205] = CreateDynamicObjectCustom(2229, -1701.2729, 78.0938, 2.6605, 0.0000, 0.00, -86.7001); //SWANK_SPEAKER
	g_Object[206] = CreateDynamicObjectCustom(955, -1718.7414, 86.4477, 3.0436, 0.0000, 0.0000, 47.4000); //CJ_EXT_SPRUNK
	g_Object[207] = CreateDynamicObjectCustom(1775, -1717.8437, 87.4010, 3.7276, 0.0000, 0.0000, 46.6999); //CJ_SPRUNK1
	g_Object[208] = CreateDynamicObjectCustom(19922, -1718.0340, 67.0457, 2.7060, 0.0000, 0.0000, -43.6999); //MKTable1
	g_Object[209] = CreateDynamicObjectCustom(2035, -1717.4104, 66.0885, 3.5004, 0.0000, 0.0000, -175.1000); //CJ_M16
	g_Object[210] = CreateDynamicObjectCustom(2035, -1717.4403, 66.4373, 3.5004, 0.0000, 0.0000, -175.1000); //CJ_M16
	g_Object[211] = CreateDynamicObjectCustom(2044, -1718.0393, 66.9710, 3.5404, 0.0000, 0.0000, 137.1000); //CJ_MP5K
	g_Object[212] = CreateDynamicObjectCustom(2044, -1717.8342, 67.1902, 3.5404, 0.0000, 0.0000, 137.1000); //CJ_MP5K
	g_Object[213] = CreateDynamicObjectCustom(2044, -1717.6153, 67.4251, 3.5404, 0.0000, 0.0000, 137.1000); //CJ_MP5K
	g_Object[214] = CreateDynamicObjectCustom(349, -1719.0716, 67.8218, 3.4567, 84.0998, -70.9000, 1.5000); //chromegun
	g_Object[215] = CreateDynamicObjectCustom(349, -1718.8177, 67.9178, 3.4577, 84.0998, -70.9000, 1.5000); //chromegun
	g_Object[216] = CreateDynamicObjectCustom(349, -1718.5360, 68.0239, 3.4576, 84.0998, -70.9000, 1.5000); //chromegun
	g_Object[217] = CreateDynamicObjectCustom(1493, -1708.9217, 85.9046, 2.6098, 0.0000, 0.00, -43.2994); //Gen_doorSHOP01
	SetDynamicObjectMaterial(g_Object[217], 1, 18065, "ab_sfammumain", "gun_door1", 0x00000000);

	new actorId;
	
	CreateDynamicActor(113, -1722.6325, 80.1791, 3.6605, 47.2000, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); //The Mafia
	CreateDynamicActor(124, -1723.1190,79.5793,3.6604,20.1843, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); //The Mafia
	actorId = CreateDynamicActor(124, -1714.9846,66.7970,3.6604,252.3665, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); //The Mafia
	ApplyDynamicActorAnimation(actorId, "COP_AMBIENT", "Copbrowse_shake", 10000.0, 0, 9999, 9999, 9999, 9999);
	actorId = CreateDynamicActor(123, -1716.6514,67.5366,3.6604,133.9488, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); //The Mafia
	ApplyDynamicActorAnimation(actorId, "DEALER", "DEALER_IDLE", 10000.0, 0, 9999, 9999, 9999, 9999);
	CreateDynamicActor(293, -1722.5638, 71.0300, 3.7005, -48.2999, .worldid = LICENSE_GUN_SHOP_WORLD, .interiorid = LICENSE_GUN_SHOP_INTERIOR); //Jeffery Cartel
}