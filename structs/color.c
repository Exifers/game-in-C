#include "structs/color.h"

struct color color_create(float r, float g, float b) {
  struct color color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

void color_dump(struct color color) {
  printf("r: %f, g: %f, b: %f", color.r, color.g, color.b);
}
