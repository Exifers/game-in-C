#include "events/events.h"

struct events *events_singleton() {
  static struct events events;
  static int set = 0;
  if (!set) {
    events = events_create();
    set = 1;
  }
  return &events;
}
