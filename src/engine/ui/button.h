#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <linmath/linmath.h>

#include "../array_list/array_list.h"
#include "../texture/texture.h"

#include "../util.h"

typedef struct {

    SDL_Rect draw_rect;    // dimensions of button
    struct {
        Uint8 r, g, b, a;
    } colour;

    bool pressed;
    bool active;
    TextureMaps *text;

} button_t;

button_t *button_get(usize index);
usize button_create(vec2 position, vec2 size, TextureMaps *text);

void button_process_event( const SDL_Event *ev);
void button_destroy( usize index);

Array_List* button_array_list_get();

#endif
