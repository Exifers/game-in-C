#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include <string.h>

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
void events_add_event(struct events *this, struct event);
struct event event_create(SDL_Event event);
void events_free(struct events *this);
void events_dump(struct events *this);
void event_dump(struct event *this);

#endif /* EVENTS_H */
