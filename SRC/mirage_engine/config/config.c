#include"../global.h"
#include"../io/io.h"
#include"../input/input_internal.h"
#include"config.h"
#include"../util.h"

#include <SDL2\SDL.h>

#include<string.h>
#include<inttypes.h>

static const char *CONFIG_DEFAULT =
	"[controls]\n"
	"left = A\n"
	"right = D\n"
	"up = W\n"
	"down = S\n"
	"space = Space\n"
	"escape = Escape\n"
	"\n";

static char tmp_buffer[15] = {0};

static char *config_get_value(const char *config_buffer, const char *value) 
{
	int i;
	char *line;
	usize len;
	char *end;
	char *curr;
	char *tmp_ptr;

	for(i = 0; i < 16; i++ )
	{
		tmp_buffer[i] = '\0';
	}

	line = strstr(config_buffer, value);
	if(!line)
	{
		ERROR_EXIT("Could not find config value: %s. "
				"Try deleting config.ini and restarting.\n", value);
	}

	len = strlen(line);
	end = line + len;

	curr = line;
	tmp_ptr = &tmp_buffer[0];
	
	// Move pointer to '='.
	while(*curr != '=' && curr != end)
	{
		++curr;
	}
	
	// Consume '='.
	++curr;
	// Consume any spaces.
	while(*curr == ' ')
	{	
		++curr;
	}
	// Get characters until end of line.
	while(*curr != '\n' && *curr != 0 && curr != end)
		
		*tmp_ptr++ = *curr++;

	*(tmp_ptr+1) = 0;

	return tmp_buffer;
	
}

static void load_controls(const char *config_buffer) 
{

	config_key_bind(INPUT_KEY_LEFT, config_get_value(config_buffer, "left"));
	config_key_bind(INPUT_KEY_RIGHT, config_get_value(config_buffer, "right"));

	config_key_bind(INPUT_KEY_UP, config_get_value(config_buffer, "up"));

	config_key_bind(INPUT_KEY_DOWN, config_get_value(config_buffer, "down"));

	config_key_bind(INPUT_KEY_SPACE, config_get_value(config_buffer, "space"));
	config_key_bind(INPUT_KEY_ESCAPE, config_get_value(config_buffer, "escape"));

}

static int config_load(void) 
{
	File file_config = io_file_read("./config.ini");
	if(!file_config.is_valid)
	{
		return 1;
	}

	load_controls(file_config.data);

	free(file_config.data);

	return 0;
}

void config_init(void) 
{
	if(config_load() == 0)
	{
		return;
	}

	io_file_write((void*)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");

	if(config_load() != 0)
	{
		ERROR_EXIT("Could not create or load config file.\n");
	}
}

void config_key_bind(Input_Key key, const char *key_name) 
{
	SDL_Scancode scan_code = SDL_GetScancodeFromName(key_name);
	if(scan_code == SDL_SCANCODE_UNKNOWN)
	{
		ERROR_RETURN(, "Invalid scan code when binding key: %s\n", key_name);
	}

	global.config.keybinds[key] = scan_code;
}
