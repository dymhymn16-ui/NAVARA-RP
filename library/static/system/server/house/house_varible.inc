/*

		House system

*/

new house_count;

enum _hinfo
{
	h_id,
	h_owner,
	h_owner_name[MAX_PLAYER_NAME-4],
	h_price,
	h_int,
	h_vw,
	Float:h_pos[4],
	Float:h_v_pos[4],
	h_icon_id,
	h_closed,
	h_rent_price,
	h_payment,
	h_area[2],
	h_renters,
	h_improve[8],
	h_cellar,
	h_safe_code,
	h_safe_data[2],
	h_safe_guns[6],
	h_prods,
	h_seed,
	h_seed_result,

	h_garage,

	h_radio_status,
	h_radio_url[128],
	h_days,
	Text3D:h_enter_label,
	Text3D:h_exit_label,
	Text3D:h_garage_label,
	h_family
};

new h_info[MAX_HOUSES][_hinfo];

#define improve_audio 			0
#define improve_doors 			1
#define improve_freeze 			2
#define improve_wardrobe 		3
#define improve_safe 			4
#define improve_sleeping	 	5
#define improve_subsidies	 	6
#define improve_cellar 			7


new h_improve_price[8] = {200000, 290000, 350000, 400000, 600000, 650000, 950000, 700000};
new h_improve_name[8][64] = {"Audio system", "Automatic doors", "Fridge", "Komod", "Gavsandoogh", "Sleeping places", "Subsidies to reduce rent", "Basement equipment"};


enum _house_int
{
	hint_class,
	Float:hint_position[4],
	Float:hspawn_position[4],
	hint_int,
	hint_description[54],
	hint_extension
};

// ----------------------------------

#define HGARAGES_COUNT 5

#define HINTS_COUNT 5

new house_classes[HINTS_COUNT][14] = {
	"Economy class",
	"Middle class",
	"High class",
	"Elite class",
	"Golden class"
};

new house_int[HINTS_COUNT][_house_int] =
{
	{1, {265.7290, 2750.3164, 804.0175, 359.7809}, {265.7479, 2751.9272, 804.0175, 359.7809}, 2, "Economy Class", 25000},
	{1, {1972.4943, -1553.1492, 2451.3472, 0.0}, {1973.5217, -1549.3590, 2451.3472, 90.0}, 2, "Middle Class", 50000},
	{1, {-104.1895, 1268.5825, 1024.5360, 91.3908}, {-106.0173, 1268.5209, 1024.5389, 91.3908}, 2, "High Class", 75000},
	{1, {325.2120, -432.9423, 1000.9105, 86.3693}, {321.697, -432.944, 1000.910, 269.633}, 2, "Elite class", 100000},
	{1, {1250.601, 1962.698, 1021.940, 266.000}, {1254.839, 1969.838, 1021.940, 180.878}, 2, "Golden class", 125000}
};

new Float:house_safe_pos[HINTS_COUNT][3] = {
	{270.1486, 2752.6765, 804.0175},
	{983.4826, 1250.0891, 1024.5360},
	{-105.6756, 1265.1408, 1028.0871},
	{310.750, -421.083, 1004.432},
	{1228.966, 1987.173, 1024.466}
};

new Float:house_freeze_pos[HINTS_COUNT][3] = {
	{261.1102, 2759.9490, 804.0175},
	{968.4531, 1240.5750, 1024.5440},
	{-115.6444, 1257.2165, 1024.5460},
	{324.2153,-454.5702,1000.9071},
	{1233.085, 1978.870, 1024.466}
};

new Float:house_bike_garage[HGARAGES_COUNT][4] = {
	{2167.3567, -371.2406, 1592.1106, 112.6875},
	{2485.6885, -2561.4097, 2501.1848, 0.0},
	{1776.0481, 4531.9165, 800.5200, -90.0},
	{-1010.2700, 1549.4760, 1328.7047, 359.4023},
	{1374.1994, -323.1918, 1001.2658, 270.7628}
};

new Float:house_veh_garage[HGARAGES_COUNT][4] = {
	{2165.7690, -373.2959, 1592.2673, 90.5659},
	{2485.6885, -2561.4097, 2501.1848, 0.0},
	{1776.6824, 4525.1191, 800.5859, -90.0},
	{-1010.2700, 1549.4760, 1328.7047, 359.4023},
	{1374.1994, -323.1918, 1001.2658, 270.7628}
};

new Float:house_garage_player_enter[HGARAGES_COUNT][4] = {
	{2169.6265, -368.4799, 1594.9048, 176.5608},
	{2495.5068,-2565.7090,2501.0859,88.3098},
	{1782.3440,4516.9688,801.2159,356.7922},
	{-1019.544, 1576.411, 1328.354, 177.510},
	{1403.503, -323.087, 1000.918,  86.708}
};

new PickupHouseGarageLeave[HGARAGES_COUNT];