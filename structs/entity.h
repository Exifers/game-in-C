#ifndef ENTITY_H
#define ENTITY_H

#include <SDL.h>

#include "structs/color.h"
#include "structs/vector.h"
#include "events/events.h"
#include "io/io.h"
#include "scene/scene.h"

enum entity_type {
		  WALL,
		  PLAYER,
		  ENEMY
};

struct entity {
  struct color color;
  struct vector dims;
  struct vector pos;
  struct vector vel;
  struct vector force;
  float mass;
  float friction;
  enum entity_type type;
  struct entity *next;
};

enum collision_type {
		     COL_TOP,
		     COL_RIGHT,
		     COL_BOTTOM,
		     COL_LEFT,
		     NONE
};

struct entity entity_create(
			    struct vector pos,
			    struct vector vel,
			    struct vector force,
			    struct vector dims,
			    float mass,
			    struct color color,
			    enum entity_type type
			    );
void entity_update(struct entity *this, float delta_time);
void entity_draw(struct entity *this);
void entity_dump(struct entity *this);

void entity_update_player(struct entity *this, float delta_time);
void entity_update_enemy(struct entity *this, float delta_time);

enum collision_type entity_collides_with(struct entity *this, struct entity *other);
static bool entity_contains(struct entity *this, struct vector point);
#endif /* ENTITY_H */
