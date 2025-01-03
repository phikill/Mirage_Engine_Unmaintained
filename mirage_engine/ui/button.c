#include "button.h"
#include "../array_list/array_list.h"
#include "../util.h"
#include "../renderer/render.h"
#include "../texture/texture.h"

#include <linmath/linmath.h>

Array_List* button_array_list;

void init_ui(){
	button_array_list = array_list_create(sizeof(button_t), 0);
}


void button_destroy( usize index ){
        array_list_remove(button_array_list, index);
}


button_t *button_get(usize index){
	return array_list_get(button_array_list, index);
}

Array_List* button_array_list_get(){

	return button_array_list;

}


usize button_create(vec2 position, vec2 size, TextureMaps *text){



    	button_t button = {

        .draw_rect = { .x = position[0], .y = position[1], .w = size[0], .h = size[1] },
        .text = text,
        .pressed = false
	};



	if (array_list_append(button_array_list, &button) == (usize)-1)
		ERROR_EXIT("Could not append button to list\n");

	return button_array_list->len - 1;

}
void button_process_event( const SDL_Event *ev) {

    for (u32 i = 0; i <= button_array_list->len; ++i) {
            button_t *btn = button_get(i);
           if( btn ) {
                // react on mouse click within button rectangle by setting 'pressed'
                if ( ev ){
                    if( ev->type == SDL_MOUSEBUTTONDOWN ) {

                        if(ev->button.button == SDL_BUTTON_LEFT &&

                                ev->button.x >= btn->draw_rect.x  * pixelScale &&
                                ev->button.x <= (btn->draw_rect.x + btn->draw_rect.w)  * pixelScale &&
                                ev->button.y >= btn->draw_rect.y   * pixelScale )
                                {
                            btn->pressed = true;
                        }
                    }
                }
        }
    }
}
