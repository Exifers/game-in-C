#ifndef IO_H
#define IO_H

#include <SDL.h>

#include "structs/color.h"
#include "structs/vector.h"

void fill_screen(struct color *color);
void draw_rect(struct vector *pos, struct vector *dims, struct color* color);
SDL_Window *window_singleton();
SDL_Surface *screen_surface_singleton();

// lifecycle hooks
int init();
int pre_event_loop();
int post_event_loop();
int end();

#endif /* IO_H */
