#include <stdlib.h>

#include "structs/scene.h"

struct scene scene_create() {
  struct scene scene;
  scene.background = color_create(50,100,255);
  scene.entities = NULL;
  return scene;
}

void scene_update(struct scene scene) {
  // handle quit
  struct event *cur = events_singleton()->event;
  while(cur) {
    printf("polling event %x\n", cur);
    if (cur->event.type == SDL_QUIT) {
      printf("quit\n");
      globals_singleton()->quit = true;
    }
    cur = cur->next;
  }
  printf("end polling event\n");
  struct entity *cur_e = scene.entities;
  while (cur_e) {
    entity_update(cur_e, 0.01f);
    cur_e = cur_e->next;
  }
}

void scene_draw(struct scene scene) {
  fill_screen(&scene.background);
  struct entity *cur = scene.entities;
  while (cur) {
    entity_draw(cur);
    cur = cur->next;
  }
}

void scene_free(struct scene scene) {
  struct entity *entity = scene.entities;
  while(entity) {
    struct entity *next = entity->next;
    free(entity);
    entity = next;
  }
}

void scene_add_entity(struct scene *this, struct entity *entity) {
  struct entity *cur = this->entities;

  if (!cur) {
    this->entities = entity;
    return;
  }

  while(cur->next) {
    cur = cur->next;
  }
  cur->next = entity;
}

void scene_dump(struct scene *this) {
  printf("scene:\n");
  printf("background: ");
  color_dump(this->background);
  printf("entities:\n");
  struct entity *cur = this->entities;
  while(cur) {
    printf(" - ");
    entity_dump(cur);
    printf("\n");
    cur = cur->next;
  }
}
