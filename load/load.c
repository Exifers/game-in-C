#include <stdio.h>
#include <stdlib.h>

#include "load/load.h"
#include "structs/vector.h"
#include "structs/color.h"
#include "structs/entity.h"

static struct entity *character_to_entity(char c) {
  enum entity_type type;
  struct color color;
  switch (c) {
  case 'x':
    type = WALL;
    color = color_create(30,30,30);
    break;
  case 'o':
    type = PLAYER;
    color = color_create(200,30,30);
    break;
  case 'v':
    type = ENEMY;
    color = color_create(30,255,100);
    break;
  default:
    return NULL;
  }

  struct entity *entity = malloc(sizeof(struct entity));
  *entity = entity_create(
			  vector_create(0,0),
			  vector_create(0,0),
			  vector_create(0,0),
			  vector_create(40,40),
			  1,
			  color,
			  type
			  );
  return entity;
}

struct scene *load_scene(char *filename) {

  // reading file
  FILE *map = fopen(filename, "r");
  if (map == NULL) {
    return NULL;
  }
  char *content = NULL;
  long length = 0;
  fseek(map, 0, SEEK_END);
  length = ftell(map);
  fseek(map, 0, SEEK_SET);
  content = malloc(length + 1);
  if (content) {
    content[length] = 0;
    fread(content, 1, length, map);
  }
  fclose(map);

  // checking format
  char *content_save = malloc(strlen(content) + 1);
  strcpy(content_save, content);
  content_save[strlen(content)] = '\0';

  char *line = strtok(content, "\n");
  int line_num = 0;
  while(line) {
    if (strlen(line) != 16) {
      return NULL;
    }
    line_num++;
    line = strtok(NULL, "\n");
  }
  if (line_num != 12) {
    return NULL;
  }
  free(content);
  content = content_save;
  
  // parsing content
  struct scene *scene = malloc(sizeof(struct scene));
  *scene = scene_create();
  
  line = strtok(content, "\n");
  line_num = 0;
  while (line) {
    for (int i = 0; i < strlen(line); i++) {
      char c = line[i];
      struct entity *entity = character_to_entity(c);
      if (!entity) { continue; }
      entity->pos = vector_create(i * 40, line_num * 40);
      scene_add_entity(scene, entity);
    }
    line = strtok(NULL, "\n");
    line_num++;
  }

  free(content);
  return scene;
}

void free_scene(struct scene *scene) {
  free(scene);
}
