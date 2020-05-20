#include "window.h"

SDL_Window *window_singleton() {
  static SDL_Window *window;
  if (window == NULL) {
    window = SDL_CreateWindow(
			      "Fuzzy",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      SCREEN_WIDTH,
			      SCREEN_HEIGHT,
			      SDL_WINDOW_SHOWN
			      );
  }
  return window;
}  
