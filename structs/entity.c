#include <stdio.h>

#include "structs/entity.h"

struct entity entity_create(
			    struct vector pos,
			    struct vector vel,
			    struct vector force,
			    struct vector dims,
			    float mass,
			    struct color color,
			    enum entity_type type
			    ) {
  struct entity entity;
  entity.pos = pos;
  entity.vel = vel;
  entity.force = force;
  entity.dims = dims;
  entity.mass = mass;
  entity.color = color;
  entity.type = type;
  entity.next = NULL;
  return entity;
}


void entity_update(struct entity *this, float delta_time) {
  struct vector dv;
  vector_cpy(&(this->force), &dv);
  vector_divf(&dv, this->mass);
  vector_mulf(&dv, delta_time);

  vector_add(&(this->vel), &dv);

  struct vector dp;
  vector_cpy(&(this->vel), &dp);
  vector_mulf(&dp, delta_time);
  vector_add(&(this->pos), &dp);
}

void entity_draw(struct entity *this) {
  draw_rect(&(this->pos), &(this->dims), &(this->color));
}

void entity_dump(struct entity *this) {
  printf("Entity of type: ");
  switch(this->type) {
  case PLAYER:
    printf("player");
    break;
  case WALL:
    printf("wall");
    break;
  case ENEMY:
    printf("enemy");
    break;
  default:
    printf("unknown?");
    break;
  }
  printf("\n");
  printf("Entity at : %f, %f.\n", this->pos.x, this->pos.y);
  printf("Dimensions : %f, %f.\n", this->dims.x, this->dims.y);
  printf("Velocity: %f, %f.\n", this->vel.x, this->vel.y);
  printf("Force: %f, %f.\n", this->force.x, this->force.y);
  printf("Color: %f, %f, %f.\n", this->color.r, this->color.g, this->color.b);
}
