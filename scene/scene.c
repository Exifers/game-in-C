#include "scene/scene.h"

struct scene *scene_singleton() {
  static struct scene scene;
  return &scene;
}
