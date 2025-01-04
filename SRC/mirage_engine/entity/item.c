#include"item.h"
#include"../array_list/array_list.h"

#include<string.h>

Array_List *item_list;
Array_List *inventory_list;


Item * item_get_item(u32 index)
{
    return array_list_get(item_list, index);
}


void item_add_inventory(Item *item)
{
    array_list_append(inventory_list, item);
}

void item_get_inventory(Item *item)
{
    array_list_get(inventory_list, item);
}

void init_item()
{
    Item letter_id_0;
    Item letter_id_1;
    Item weapon_id_2;
    Item health_id_3;
    Item key_house_id_4;

    letter_id_0.item_type_enum = LETTER;
    letter_id_0.amount = 1;
    letter_id_0.charge = 0;
    letter_id_0.damage = 0;
    //letter_id_0.dialogue = "Letter Dropped: Dear PEASANTS, Stop messing my stuff";
    strcpy(letter_id_0.dialogue, "Letter Dropped: Dear PEASANTS, Stop messing my stuff");
    
    letter_id_1.item_type_enum = LETTER;
    letter_id_1.amount = 1;
    letter_id_1.charge = 0;
    letter_id_1.damage = 0;
    //letter_id_1.dialogue = "Letter Dropped: I Fear what they think seeing me.";
    strcpy(letter_id_1.dialogue, "Letter Dropped: I Fear what they think seeing me.");

    weapon_id_2.item_type_enum = WEAPON;
    weapon_id_2.amount = 1;
    weapon_id_2.charge = 1;
    weapon_id_2.damage = 1000;
    strcpy(weapon_id_2.dialogue, "They Dropped An Old Projectile Contraption.");
    strcpy(weapon_id_2.name, "Contraption");

    health_id_3.item_type_enum = HEALLING;
    health_id_3.amount = 1;
    health_id_3.hecharge = 100;
    health_id_3.charge = 1;
    health_id_3.damage = 0;
    strcpy(health_id_3.dialogue, "They Dropped A Healing Potion.");
    strcpy(health_id_3.name, "Healing");

    key_house_id_4.item_type_enum = ITEM_KEY_HOUSE;
    key_house_id_4.amount = 1;
    key_house_id_4.hecharge = 0;
    key_house_id_4.charge = 1;
    key_house_id_4.damage = 0;
    strcpy(key_house_id_4.dialogue, "They Dropped A Key.");
    strcpy(key_house_id_4.name, "Door Key");

    item_list = array_list_create(sizeof(Item), 0);
    array_list_append(item_list, &letter_id_0);
    array_list_append(item_list, &letter_id_1);
    array_list_append(item_list, &weapon_id_2);
    array_list_append(item_list, &health_id_3);
    array_list_append(item_list, &key_house_id_4);

}

