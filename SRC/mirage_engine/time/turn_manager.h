#ifndef TURNM_MANAGER_H
#define TURNM_MANAGER_H

#include "../entity/entity.h"


void init_turn(Entity * first_character_in_turn, 
               Entity *second_character_in_turn);

typedef struct
{

    Entity *entity_in_current_turn[2];
    Entity *character_current_turn;

    bool active;
    int current_size_of_turn_size;

} Current_Turn;

Current_Turn *get_active_turn();


#endif
