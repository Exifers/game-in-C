#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "structs/vector.h"
#include "structs/color.h"
#include "structs/entity.h"
#include "io/io.h"
#include "structs/scene.h"
#include "load/load.h"
#include "events/events.h"
#include "globals/globals.h"

int main(void) {
  if (init()) {
    printf("Failed initialization.\n");
    return -1;
  }

  struct scene *scene = scene_singleton();
  *scene = *load_scene("./maps/1.map");
  if (!scene) {
    printf("Failed to load scene.\n");
    return -1;
  }

  float t = 0;
  while(globals_singleton()->quit == false) {
    if (pre_event_loop()) {
      printf("Failed pre event loop.\n");
      return -1;
    }
    poll_events();

    t += 0.1;
    
    scene_update(*scene);
    scene_draw(*scene);

    reset_events();
    if (post_event_loop()) {
      printf("Failed post event loop.\n");
      return -1;
    }
  }

  if (end()) {
    printf("Failed ending program.\n");
    return -1;
  }

  return 0;
}
