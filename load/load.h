#ifndef LOAD_H
#define LOAD_H

#include "structs/scene.h"

struct scene *load_scene(char *filename);
void free_scene(struct scene *scene);

#endif /* LOAD_H */
