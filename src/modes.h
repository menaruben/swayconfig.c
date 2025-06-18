#ifndef __MODES_H__
#define __MODES_H__

#include "keybindings.h"

typedef struct {
  const char *name;
  const Keybind_t **keybinds; // null terminated array
} Mode_t;

static void print_mode(const Mode_t *mode) {
  printf("mode \"%s\" {\n", mode->name);

  for (size_t i = 0; mode->keybinds[i] != NULL; i++) {
    print_keybind(mode->keybinds[i]);
  }

  printf("}\n");
}

void print_modes(const Mode_t **modes, size_t mode_count) {
  for (size_t i = 0; i < mode_count; i++) {
    if (modes[i] != NULL) {
      print_mode(modes[i]);
    }
  }
}

#endif
