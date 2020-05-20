#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

struct color {
  float r;
  float g;
  float b;
};

struct color color_create(float r, float g, float b);
void color_dump(struct color color);

#endif /* COLOR_H */
