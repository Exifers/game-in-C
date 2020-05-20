#ifndef ENTITY_H
#define ENTITY_H

#include "structs/color.h"
#include "structs/vector.h"
#include "io/io.h"

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
  enum entity_type type;
  struct entity *next;
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

#endif /* ENTITY_H */