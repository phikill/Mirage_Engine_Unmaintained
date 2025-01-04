#ifndef INPUT_INTERNAL_H
#define INPUT_INTERNAL_H

#pragma once

#include <stdbool.h>

typedef enum input_key 
{
	INPUT_KEY_LEFT,
	INPUT_KEY_RIGHT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_ESCAPE,
	INPUT_KEY_SPACE
} Input_Key;

typedef enum key_state 
{
	KS_UNPRESSED,
	KS_PRESSED,
	KS_HELD
} Key_State;

typedef struct input_state 
{
	
	Key_State left;
	Key_State right;
	Key_State up;
	Key_State down;
	Key_State escape;
	Key_State space;

} Input_State;

void input_update();

#endif /* INPUT_INTERNAL_H */
