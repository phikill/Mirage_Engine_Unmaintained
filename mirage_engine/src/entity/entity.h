#ifndef ENTITY_H
#define ENTITY_H
#include <stdbool.h>
#include <linmath/linmath.h>
#include "../physics/physics.h"
#include "../array_list/array_list.h"
#include "../util.h"

#include "../types.h"
#include "../NPC/mind_npc.h"
#include "../renderer/render.h"

typedef void (*Entity_Delete)(u32 entity_id);
typedef void (*Entity_Health_Change)(u32 amount);
typedef void (*Update_Mind)(u32 amount);

typedef enum Mind_State_Enums {
    NOTHING = 0 ,
    IDLE,
    WALK,
    JUMP,
    ATTACK,
    DEATH,

}Mind_State_Enums;

typedef enum  {

    NEUTRAL_STANCE = 0 ,
    LEFT_STANCE ,
    RIGHT_STANCE,

}Mind_State_Stance;

typedef enum NPC_Alignment_Enums {


    LAWFUL = 0 ,
    NEUTRAL,
    CHAOTIC,

}NPC_Alignment;

typedef enum CHAR_SPACE {

    CAMERA = 0 ,
    LEFT,
    RIGHT,

}CHAR_SPACE;


typedef struct {

    u32 damage;
    int range;
    int travel;
    int id;

} Power_Deffinition_mod;

typedef struct {

    int gun_damage_max;
    int ammo;

} Gun;

typedef struct MIND_NPC{

NPC_Alignment mind_alliment;
u16                     dir;
u16                     mod;
u16             power_level;
Update_Mind     update_mind;
u32               entity_id;
bool              can_atack;

}Mind_NPC;

typedef struct entity {

    CHAR_SPACE player_index;
    usize body_id;
    u32 dialogue_id;
    char name_entity[NAME_SIZE];
	usize id;

	usize animation_id;
	usize person_of_interest_id;
    vec2 sprite_offset;
    vec2 sprite_pos;

	bool is_active;
    bool is_enraged;
    bool should_draw_on_scene;
    bool is_turn_set;
	bool is_playble;
	bool is_npc;

	bool is_in_party;

    Mind_State_Stance stance;

    u8 health;
    bool should_draw;
    Mind_State_Enums npc_state;
    u32 texture_id;
    u32 ws;
    u32 we;
    u32 sector;
    u32 item_hoilding;
    Mind_NPC *mind;

    Power_Deffinition_mod  *table_mod;
    Entity_Health_Change health_change;
    Entity_Delete entity_delete_event;
    char dialogue[DIALOGUE_SIZE];
    Body *entity_body;

    int index_in_turn;
    int drawing_other;

    u32 attacks[2];



} Entity;

void entity_init(void);



usize entity_create( Mind_NPC *mind, CHAR_SPACE player_index, vec3 position, vec3 size, vec3 sprite_offset, vec3 velocity, u8 collision_layer, u8 collision_mask, bool is_kinematic, usize animation_id, On_Hit on_hit, On_Hit_Static on_hit_static, Mind_State_Enums npc_state, NPC_Alignment alignment, u32 health, Entity_Delete entity_delete_event, Entity_Health_Change health_change, bool playble, u32 texture_id,  u32 dialogue_id, int sector, int a, int l, int item_hoilding );

Entity *entity_get(usize id);
usize entity_count(void);
void entity_reset(void);
Entity *entity_by_body_id(usize body_id);
usize entity_id_by_body_id(usize body_id);

Array_List *entity_array_list_get();

// Returns true if the enemy dies.
bool entity_damage(u32 entity_id, u8 amount,f32 delta_time);
void entity_destroy(usize entity_id);

void entity_destroy_from_memory(usize entity_id);

#endif
