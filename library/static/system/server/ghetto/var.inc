/*

		Gangzones

*/
#define gz_type_kills 		0
#define gz_type_count 		1
#define MAX_GANGZONE  		110

new gz_count = 0,
	gz_captured = -1,
	gz_capture_type;


new owner_points = -1,
	attacker_points = -1;

enum _gz_info
{
	gz_id,
	gz_created,
	Float:gz_pos[4],
	gz_owner,
	gz_attacker,
	gz_time,
	gz_timer,
	gz_kills[2]
}
new gz_info[MAX_GANGZONE][_gz_info];

new capture_gang_cd[5];
new capture_gang_freezed[5];

#define MAX_SPAWN_ZONE 6

enum _spawn_info
{
	spawn_area,
	spawn_owner
}

new spawn_zone[MAX_SPAWN_ZONE][_spawn_info];