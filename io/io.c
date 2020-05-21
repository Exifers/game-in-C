#include <SDL.h>

#include "io/window.h"
#include "io/screen.h"
#include "io/io.h"
#include "events/events.h"
#include "structs/events.h"

/* converters */

static Uint32 color_to_SDL_RGB(struct color *color) {
  return SDL_MapRGB(screen_surface_singleton()->format, color->r, color->g, color->b);
}

/* API */

// Fills the event singleton with the events that happened on the current frame.
// Call this function once per frame and then all events are readable in the
// event singleton.
void poll_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.key.repeat) {
      continue;
    }
    events_add_event(events_singleton(), event_create(event));
  }
}

// Empty event singleton. Call this function once per frame at the end of the
// game loop so that only fresh events appear in the singleton on the next
// frame.
void reset_events() {
  events_free(events_singleton());
}

bool key_pressed(SDL_Keycode key) {
}

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

// key state
bool key_is_pressed(SDL_Keycode keycode) {
  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_GetScancodeFromKey(keycode)]) {
    return true;
  }
  return false;
}

// key event
bool key_is_pressed_this_frame(SDL_Keycode keycode) {
  struct events *events = events_singleton();
  struct event *cur = events->event;
  while(cur) {
    if (cur->event.type == SDL_KEYDOWN) {
      if (cur->event.key.keysym.sym == keycode) {
	return true;
      }
    }
    cur = cur->next;
  }
  return false;
}
