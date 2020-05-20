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

int main(void) {

  if (init()) {
    printf("Failed initialization.\n");
    return -1;
  }

  struct scene *scene = load_scene("./maps/1.map");
  if (!scene) {
    printf("Failed to load scene.\n");
    return -1;
  }
  scene_dump(scene);

  float t = 0;
  int quit = 0;
  while(quit == 0) {
    if (pre_event_loop()) {
      printf("Failed pre event loop.\n");
      return -1;
    }

    t += 0.1;
    
    scene_update(*scene);
    scene_draw(*scene);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch(event.type) {
	case SDL_QUIT:
	  quit=1;
	  break;
      }
    }

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
