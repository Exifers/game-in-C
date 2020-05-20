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

void events_add_event(struct events *this, struct event event) {
  struct event *event_ = malloc(sizeof(struct event));
  *event_ = event;

  struct event *cur = this->event;
  if (!cur) {
    this->event = event_;
    return;
  }
  while(cur->next) {
    cur = cur->next;
  }
  cur->next = event_;
}

void events_free(struct events *events) {
  struct event *cur = events->event;
  if (!cur) {
    return;
  }
  while(cur->next) {
    struct event *next = cur->next;
    free(cur);
    cur = next;
  }
  free(cur);
  events->event = NULL;
}

void events_dump(struct events *this) {
  struct event *cur = this->event;
  while(cur) {
    printf("-");
    event_dump(cur);
    printf("\n");
    cur = cur->next;
  }
}

void event_dump(struct event *this) {
  printf("an event");
}
