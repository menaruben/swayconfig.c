#ifndef __HELPERS_H__
#define __HELPERS_H__

#define SWITCH_WORKSPACE(kb_source, kb_dest)                               \
    (Keybind_t)                                                            \
    {                                                                      \
        .description = "Switch workspace mapping",                         \
        .keys = KEYS(MODIFIER_KEY(Mod), LITERAL_KEY(kb_source)),           \
        .command = (const char *[]){"workspace", "number", kb_dest, NULL}, \
    }

#define MOVE_TO_WORKSPACE(kb_source, kb_dest)                                     \
    (Keybind_t)                                                                   \
    {                                                                             \
        .description = "Move container to a workspace",                           \
        .keys =                                                                   \
            KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Shift), LITERAL_KEY(kb_source)), \
        .command = (const char *[]){"move", "container", "to", "workspace",       \
                                    "number", kb_dest, NULL},                     \
    }

#define MOVE_FOCUS(key, direction)                             \
    (Keybind_t)                                                \
    {                                                          \
        .description = "Move focus to specific direction",     \
        .keys = KEYS(MODIFIER_KEY(Mod), SPECIAL_KEY(key)),     \
        .command = (const char *[]){"focus", direction, NULL}, \
    }

#define MOVE_DIRECTION(key, direction)                                          \
    (Keybind_t)                                                                 \
    {                                                                           \
        .description = "Move container in a direction",                         \
        .keys = KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Shift), SPECIAL_KEY(key)), \
        .command = (const char *[]){"move", direction, NULL},                   \
    }

#define RESIZE_SHRINK "shrink"
#define RESIZE_GROW "grow"
#define RESIZE_WINDOW_WIDTH "width"
#define RESIZE_WINDOW_HEIGHT "height"
#define RESIZE_WINDOW(key, shrink_or_grow, width_or_height)                                   \
    (Keybind_t)                                                                               \
    {                                                                                         \
        .description = "Resize window in a direction",                                        \
        .keys = KEYS(SPECIAL_KEY(key)),                                                       \
        .command = (const char *[]){"resize", shrink_or_grow, width_or_height, "10px", NULL}, \
    }

#endif