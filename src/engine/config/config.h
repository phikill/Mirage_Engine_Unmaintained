#pragma once

#include "../input/input_internal.h"
#include <inttypes.h>
#include "../types.h"


typedef struct config {

	u8 keybinds[7];

} Config_State;

void config_init(void);
void config_key_bind(Input_Key key, const char *key_name);