#include <SDL.h>

#include "io/window.h"
#include "io/screen.h"
#include "io/io.h"

/* converters */

static Uint32 color_to_SDL_RGB(struct color *color) {
  return SDL_MapRGB(screen_surface_singleton()->format, color->r, color->g, color->b);
}

/* API */

void fill_screen(struct color *color) {
  SDL_FillRect(
	       screen_surface_singleton(),
	       NULL,
	       SDL_MapRGB(
			  screen_surface_singleton()->format,
			  color->r,
			  color->g,
			  color->b
			  )
	       );
}

void draw_rect(struct vector *pos, struct vector *dims, struct color* color) {
  SDL_Rect rect;
  rect.x = pos->x;
  rect.y = pos->y;
  rect.w = dims->x;
  rect.h = dims->y;
  SDL_FillRect(screen_surface_singleton(), &rect, color_to_SDL_RGB(color));
}

int init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return -1;
  }

  SDL_Window* window = window_singleton();
  screen_surface_singleton();

  if (window == NULL) {
    return -1;
  }
  return 0;
}

int pre_event_loop() {
  return 0;
}

int post_event_loop() {
  SDL_Window *window = window_singleton();
  SDL_UpdateWindowSurface(window);
}

int end() {
  SDL_Window *window = window_singleton();
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
