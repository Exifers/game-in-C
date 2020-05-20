#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdbool.h>
#include <string.h>

struct globals {
  bool quit;
};

struct globals *globals_singleton();

#endif /* GLOBALS_H */
