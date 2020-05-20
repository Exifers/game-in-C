#include "io/screen.h"

SDL_Surface *screen_surface_singleton() {
  static SDL_Surface *screen_surface;
  SDL_Window *window = window_singleton();
  if (screen_surface == NULL) {
    screen_surface = SDL_GetWindowSurface(window);
  }
  return screen_surface;
}

