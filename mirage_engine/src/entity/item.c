#include "item.h"
#include "../array_list/array_list.h"


Array_List *item_list;
Array_List *inventory_list;


Item * item_get_item(u32 index){

          return array_list_get(item_list, index);

}


void item_add_inventory(Item *item ){

    array_list_append(inventory_list, item);

}

void item_get_inventory(Item *item ){

    array_list_get(inventory_list, item);

}

void init_item(){

    Item letter_id_0 =  {

            .item_type_enum = LETTER,
            .amount = 1,
            .charge = 0,
            .damage = 0,
            .dialogue = "Letter Dropped: Dear PEASANTS, Stop messing my stuff",
            
    };
    
    Item letter_id_1 =  {

            .item_type_enum = LETTER,
            .amount = 1,
            .charge = 0,
            .damage = 0,
            .dialogue = "Letter Dropped: I Fear what they think seeing me.", 

    };

    Item weapon_id_2 =  {

            .item_type_enum = WEAPON,
            .amount = 1,
            .charge = 1,
            .damage = 1000,
            .dialogue = "They Dropped An Old Projectile Contraption.", 
            .name = "Contraption"

    };

    Item health_id_3 =  {

            .item_type_enum = HEALLING,
            .amount = 1,
            .hecharge = 100,
            .charge = 1,
            .damage = 0,
            .dialogue = "They Dropped A Healing Potion.", 
            .name = "Healing"

    };

    Item key_house_id_4 =  {

            .item_type_enum = ITEM_KEY_HOUSE,
            .amount = 1,
            .hecharge = 0,
            .charge = 1,
            .damage = 0,
            .dialogue = "They Dropped A Key.", 
            .name = "Door Key"

    };

    item_list = array_list_create(sizeof(Item), 0);
    array_list_append(item_list, &letter_id_0);
    array_list_append(item_list, &letter_id_1);
    array_list_append(item_list, &weapon_id_2);
    array_list_append(item_list, &health_id_3);
    array_list_append(item_list, &key_house_id_4);

}