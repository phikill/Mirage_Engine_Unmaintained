#ifndef ITEM_H
#define ITEM_H
#include<stdbool.h>
#include<linmath/linmath.h>
#include"../array_list/array_list.h"
#include"../util.h"

#include"../types.h"


typedef enum item_enum 
{
    LETTER = 0,
    WEAPON,
    HEALLING,
    ITEM_KEY_HOUSE,
} Item_Enum;

typedef struct item 
{
    Item_Enum item_type_enum;
    u32 amount;
    u32 charge;
    u32 hecharge;
    u32 index_in_inventory;
    u32 index_button;
    u32 damage;
    char dialogue[DIALOGUE_SIZE];
    char name[DIALOGUE_SIZE];
} Item;

void init_item();
Item * get_item(u32 index);

#endif
