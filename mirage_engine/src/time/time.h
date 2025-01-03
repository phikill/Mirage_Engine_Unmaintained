#pragma once 

#ifndef TIME_H
#define TIME_H

#include <inttypes.h>
#include "../types.h"


typedef void (*on_time_out_tree_delay)(u32 caller_id, u32 value, f32 current_time);

typedef struct time_tree_delays{

	u32 caller_id;
	f32 tree_delay;
	u32 value;

} time_tree_delay;


typedef struct time_observers{

	on_time_out_tree_delay on_time_tree_delay;
	time_tree_delay time_delay;

} time_observer;

void time_reset_observer_list();

typedef struct time_state {
	f32 delta;
	f32 now;
	f32 last;

	f32 frame_last;
	f32 frame_delay;
	f32 frame_time;

	u32 frame_rate;
	u32 frame_count;

} Time_State;



void time_init(u32 frame_rate);
void time_update(void);
void time_update_late(void);
void create_time_tree_timer(on_time_out_tree_delay on_time_out_event, usize id_of_caller, u32 value, f32 time_delay );
void time_change(u32 frame_rate);

time_tree_delay *get_tree_timer_array_list(u32 id, u32 value);

#endif