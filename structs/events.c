#include "structs/events.h"

struct event event_create(SDL_Event sdl_event) {
  struct event event;
  event.event = sdl_event;
  event.next = NULL;
  return event;
}

struct events events_create() {
  struct events events;
  events.event = NULL;
  return events;
}
