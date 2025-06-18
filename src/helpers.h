#ifndef __HELPERS_H__
#define __HELPERS_H__

#include "keys.h"

#define ARRAY(...) {__VA_ARGS__, NULL}
#define ARRAY_OF(T, ...)                                                       \
  (T *[]) { __VA_ARGS__, NULL }

#define EXEC(...) ARRAY("exec", __VA_ARGS__)

#define EXEC_SH(...) EXEC("sh", "-c", "'", __VA_ARGS__, "'")

#define SWITCH_WORKSPACE(kb_source, kb_dest)                                   \
  (Keybind_t) {                                                                \
    .description = "Switch workspace mapping",                                 \
    .keys = ARRAY_OF(Key_t, Mod, LITERAL(kb_source)),                          \
    .command = (const char *[]){"workspace", "number", kb_dest, NULL},         \
  }

#define MOVE_TO_WORKSPACE(kb_source, kb_dest)                                  \
  (Keybind_t) {                                                                \
    .description = "Move container to a workspace",                            \
    .keys = ARRAY_OF(Key_t, Mod, Shift, LITERAL(kb_source)),                   \
    .command = (const char *[]){"move",   "container", "to", "workspace",      \
                                "number", kb_dest,     NULL},                  \
  }

#define MOVE_FOCUS(key, direction)                                             \
  (Keybind_t) {                                                                \
    .description = "Move focus to specific direction",                         \
    .keys = ARRAY_OF(Key_t, Mod, key),                                         \
    .command = (const char *[]){"focus", direction, NULL},                     \
  }

#define MOVE_DIRECTION(key, direction)                                         \
  (Keybind_t) {                                                                \
    .description = "Move container in a direction",                            \
    .keys = ARRAY_OF(Key_t, Mod, Shift, key),                                  \
    .command = (const char *[]){"move", direction, NULL},                      \
  }

#define RESIZE_SHRINK "shrink"
#define RESIZE_GROW "grow"
#define RESIZE_WINDOW_WIDTH "width"
#define RESIZE_WINDOW_HEIGHT "height"

#define RESIZE_WINDOW(key, shrink_or_grow, width_or_height)                    \
  (Keybind_t) {                                                                \
    .description = "Resize window in a direction",                             \
    .keys = ARRAY_OF(Key_t, key),                                              \
    .command = (const char *[]){"resize", shrink_or_grow, width_or_height,     \
                                "10px", NULL},                                 \
  }

#endif
