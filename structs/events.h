#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

// A linked list of events updated on each frame so that any part of the program can
// read what events happened on the current frame. Based on SDL_Event SDL data type.
// To read if a key is pressed on the keyboard, use the SDL wrapper function in io/.
struct event {
  SDL_Event event;
  struct event *next;
};

struct events {
  struct event *event;
};

struct events events_create();
struct event event_create(SDL_Event event);

#endif /* EVENTS_H */
