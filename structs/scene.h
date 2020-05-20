#ifndef SCENE_H
#define SCENE_H

#include "structs/color.h"
#include "structs/entity.h"

struct scene {
  struct entity *entities;
  struct color background;
};

struct scene scene_create();
void scene_free(struct scene scene);
void scene_draw(struct scene scene);
void scene_update(struct scene scene);
void scene_add_entity(struct scene *this, struct entity *entity);
void scene_dump(struct scene *this);

#endif /* SCENE_H */
