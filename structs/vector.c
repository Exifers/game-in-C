#include <stdio.h>

#include "structs/vector.h"

struct vector vector_create(float x, float y) {
  struct vector vector;
  vector.x = x;
  vector.y = y;
  return vector;
}

void vector_add(struct vector *this, struct vector *other) {
  this->x += other->x;
  this->y += other->y;
}

void vector_sub(struct vector *this, struct vector *other) {
  this->x -= other->x;
  this->y -= other->y;
}

void vector_divf(struct vector *this, float coef) {
  if (coef == 0) {
    return;
  }
  this->x /= coef;
  this->y /= coef;
}

void vector_cpy(struct vector *this, struct vector *other) {
  other->x = this->x;
  other->y = this->y;
}

void vector_mulf(struct vector *this, float coef) {
  this->x *= coef;
  this->y *= coef;
}

void vector_print(struct vector *this) {
  printf("[%f,%f]\n", this->x, this->y);
}
