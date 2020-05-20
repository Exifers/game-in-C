#include "globals/globals.h"

struct globals *globals_singleton() {
  static struct globals globals;
  static bool set = false;
  if (!set) {
    globals.quit = false;
    set = 1;
  }
  return &globals;
}
