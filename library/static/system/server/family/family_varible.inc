const max_family = 500;

enum _fam_enum_
{
    fam_id,
    fam_type,
    fam_name[68],
    fam_chat_color[8],
    fam_creator[MAX_PLAYER_NAME],
    fam_nationality,
    fam_settings[9],

    fam_bank,
    fam_house,

    fam_vip,

    fam_drugs,
    fam_materials,
    fam_guns,
    fam_dorm_status,

    fam_members,

    fam_rating,
    fam_ticket,

    fam_max_car,
}
new family_info[max_family][_fam_enum_], family_count = 0;

#define MAX_SLOT_FAMILY_VEHICLES 10
#define MAX_SLOT_FAMILY_MEMBERS 15

#define MAX_SLOT_FAMILY_VIP_VEHICLES 20

new family_rank[max_family][20][30];

new Iterator:family_players[max_family]<MAX_PLAYERS-1>;
new Iterator:family_vehicles[max_family]<MAX_VEHICLES-1>;

new family_cars[max_family] = {0, ...};
new family_chat_color[5][8] = {"FFFFFF","FFD39B","FFFF00","54FF9F","98F5FF"};