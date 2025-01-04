#include "time.h"
#include "../global.h"
#include "../types.h"
#include "../util.h"

#include "../array_list/array_list.h"
#include <stdbool.h>>
static Array_List *array_list_of_tree_delay;
static Array_List *tree_time_callers;
static Array_List *observers_array_list;


void time_init(u32 frame_rate) 
{
	array_list_of_tree_delay = array_list_create(sizeof(time_tree_delay), 0);
	observers_array_list = array_list_create(sizeof(time_observer), 0);

	tree_time_callers  = array_list_create(sizeof(u32), 0);
	global.time.frame_rate = frame_rate;
	global.time.frame_delay = 1000.f / frame_rate;
}

void time_update(void) 
{
	global.time.now = (f32)SDL_GetTicks();
	global.time.delta = (global.time.now - global.time.last) / 1000.f;
	global.time.last = global.time.now;
	++global.time.frame_count;

	if(global.time.now - global.time.frame_last >= 1000.f) 
	{
		global.time.frame_rate = global.time.frame_count;
		global.time.frame_count = 0;
		global.time.frame_last = global.time.now;
	}

    if( observers_array_list->len > 0 )
    {
		for(u32 i = 0; i <= observers_array_list->len; i++) 
		{
			time_observer * tree_observer = array_list_get(observers_array_list, i);

			if(tree_observer != NULL)
			{
				tree_observer->time_delay.tree_delay -= global.time.delta;
				if(tree_observer->time_delay.tree_delay <= 0)
				{
					tree_observer->on_time_tree_delay(tree_observer->time_delay.caller_id,
													  tree_observer->time_delay.value, 
								 					  0);
					array_list_remove(observers_array_list, i);
					tree_observer = NULL;		
				}
			}
		}
	}
}

void time_update_late()
{
	global.time.frame_time = (f32)SDL_GetTicks() - global.time.now;

	if(global.time.frame_delay > global.time.frame_time) 
	{
		SDL_Delay(global.time.frame_delay - global.time.frame_time);
	}
}

void time_reset_observer_list()
{

	for( u32 i = 0; i <= observers_array_list->len; ++i ) 
	{
		if( array_list_get(observers_array_list, i) != NULL)
		{
			time_observer * tree_observer = array_list_get(observers_array_list, i);

			tree_observer->on_time_tree_delay(tree_observer->time_delay.caller_id,
											  tree_observer->time_delay.value, 
											  0);
			array_list_remove(observers_array_list, i);
		}
	}

	observers_array_list->len = 0;
}

void create_time_tree_timer(on_time_out_tree_delay on_new_time_out_event, 
							usize id_of_caller, 
							u32 value, 
							f32 time_delay )
{
	u32 id = (u32)id_of_caller;

	bool found = false;
	if(observers_array_list->len > 0)
	{

		for(u32 i = 0; i <= observers_array_list->len; i++) 
		{
			if(array_list_get(observers_array_list, i) != NULL)
			{
				time_observer *observer = array_list_get(observers_array_list,i);

				if(observer->time_delay.caller_id  == id )
				{
					found = true;
					break;

				}
			}
		}
	}

	if ( found == false )
	{

		if (array_list_append(observers_array_list, &(time_observer){0}) == (usize)-1) 
		{
			ERROR_EXIT("Could not append to time list\n");
		}
		
		time_observer * time_observer_ = array_list_get(observers_array_list, observers_array_list->len - 1);

		time_observer_->on_time_tree_delay = on_new_time_out_event;
		time_observer_->time_delay.tree_delay =  time_delay;
		time_observer_->time_delay.caller_id = id;
		time_observer_->time_delay.value = value;
	}
}
