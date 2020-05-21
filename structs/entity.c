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
  entity.friction = 0.95;
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

  vector_mulf(&(this->vel), this->friction);

  switch (this->type) {
  case PLAYER:
    entity_update_player(this, delta_time);
    break;
  case ENEMY:
    entity_update_enemy(this, delta_time);
    break;
  default:
    break;
  }

  if (this->type == PLAYER || this->type == ENEMY) {
    // collisions against walls, frame borders and gravity
    struct entity *cur = scene_singleton()->entities;
    while (cur) {
      if (cur != this && cur->type == WALL) {
	if (entity_collides_with(this, cur) == COL_RIGHT) {
	  this->vel = vector_create(-1,0);
	}
	 if (entity_collides_with(this, cur) == COL_LEFT) {
	  this->vel = vector_create(1,0);
	}
	 //	if (entity_collides_with(this, cur) == COL_BOTTOM) {
	 //	  this->vel = vector_create(0,-1);
	 //	}
      }
      cur = cur->next;
    }

    // gravity
    //    struct vector gravity = vector_create(0,2);
    //    vector_add(&this->force, &gravity);
  }
}

static bool entity_contains(struct entity *this, struct vector point) {
  struct vector pos = this->pos;
  struct vector dims = this->dims;

  return pos.x <= point.x && point.x <= pos.x + dims.x \
    && pos.y <= point.y && point.y <= pos.y + dims.y;
}

enum collision_type entity_collides_with(struct entity *this, struct entity *other) {
  struct vector p1 = this->pos;
  if (entity_contains(other, p1)) {
    return COL_LEFT;
  }

  p1 = this->pos;
  struct vector dx1 = vector_create(this->dims.x, 0);
  vector_add(&p1, &dx1);
  if (entity_contains(other, p1)) {
    return COL_RIGHT;
  }

  p1 = this->pos;
  struct vector dy1 = vector_create(0, this->dims.y);
  vector_add(&p1, &dy1);
  if (entity_contains(other, p1)) {
    return COL_BOTTOM;
  }

  p1 = this->pos;
  struct vector dxy1 = this->dims;
  vector_add(&p1, &dxy1);
  if (entity_contains(other, p1)) {
    return COL_BOTTOM;
  }

  return false;
}

void entity_update_player(struct entity *this, float delta_time) {
  // controls
  if (key_is_pressed(SDLK_RIGHT)) {
    struct vector v = vector_create(10,0);
    vector_add(&(this->vel), &v);
  }
  if (key_is_pressed(SDLK_LEFT)) {
    struct vector v = vector_create(-10,0);
    vector_add(&(this->vel), &v);
  }
  if (key_is_pressed_this_frame(SDLK_SPACE)) {
    struct vector v = vector_create(0,-30);
    vector_add(&(this->vel), &v);
  }
}

void entity_update_enemy(struct entity *this, float delta_time) {
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
