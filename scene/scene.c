#include "scene/scene.h"

struct scene *scene_singleton() {
  static struct scene scene;
  static int set = 0;
  if (!set) {
    scene = scene_create();
    set = 1;
  }
  return &scene;
}
