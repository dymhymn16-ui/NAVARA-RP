/*
			fractions
*/

#define max_rank 		16
#define max_fraction	32
new fraction_count;

enum _fractions
{
	f_id,
	f_name[48],
	Float:f_spawn[4],
	f_spawn_int,
	f_spawn_virt,
	f_money,
	f_materials,
	f_drugs,
	f_guns,
	f_dorm_status,
	f_radar_color,
	f_chat_color[8],
	f_leader_name[MAX_PLAYER_NAME],
	f_rank_settings[5],
	f_rank_salary[max_rank],
	f_capture,
	f_money_limit,

	Float:tp_pos[4],
	tp_mapicon,
	Text3D:tp_label
};

new f_info[max_fraction][_fractions];

new f_rank[max_fraction][max_rank][24];
new f_skin[max_fraction][2][max_rank];

#define GetFractionName(%0) f_info[%0][f_name]

#define dip_status_neutral 0
#define dip_status_war 1
#define dip_status_alliance 2
#define dip_status_alliance_invite 3
#define dip_status_alliance_get_invite 4


new Float: dorm_pos[8][3] = {
	{2489.67, -1730.23, 2954.03},
	{1977.49, -1143.18, 2497.59},
	{2863.32, 1695.60, 1109.83},
	{2899.50, 1576.20, 1119.95},
	{2799.86, -1942.30, 1333.75},
	{-1471.6904, 306.4484, 1059.9917},
	{-2624.6802, 49.0959, 1960.1409},
	{2033.2272, -1998.5955, 1073.2142}
};

new Text3D:gdorm_text[8];

new f_diplomacy[8][8];