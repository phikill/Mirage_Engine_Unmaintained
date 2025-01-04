#include <stdarg.h>
#include "turn_manager.h"
#include "../util.h"
#include "../types.h"
#include "../entity/entity.h"


Current_Turn* current_turn_entity;

void init_turn(Entity *first_character_in_turn, 
               Entity *second_character_in_turn)
{

	*current_turn_entity = (Current_Turn)
    {

        .entity_in_current_turn[0] = first_character_in_turn,
        .entity_in_current_turn[1] = second_character_in_turn,

        .character_current_turn = first_character_in_turn,
        .active = true,
    };
}

void init_turn_manager()
{
    current_turn_entity = malloc(sizeof(Current_Turn));
    current_turn_entity->character_current_turn = NULL;
}


void add_to_turn(Entity *new_character_in_turn)
{

    for(int i = 0; i < 5; i++)
    {
        if(current_turn_entity->entity_in_current_turn[i] == NULL )
        {

            current_turn_entity->entity_in_current_turn[i] = new_character_in_turn;
            break;
        }
    }
}

void end_to_turn()
{
    for(int i = 0; i < 2; i++)
    {
        current_turn_entity->entity_in_current_turn[i] = NULL;
    }
    current_turn_entity->character_current_turn = NULL;
}


int get_turn_size()
{
    return current_turn_entity->current_size_of_turn_size;
}


Current_Turn *get_active_turn()
{
    return current_turn_entity;
}
