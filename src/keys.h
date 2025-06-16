#ifndef __KEYS_H__
#define __KEYS_H__

#include "variables.h"
#define SuperKey "Mod4"
#define AltKey "Mod1"

typedef enum
{
    Mod,
    Return,
    Ctrl,
    Alt,
    Shift,
    CapsLock
} ModifierKey_t;

typedef enum
{
    Escape,
    Tab,
    Space,
    Insert,
    Delete,
    Home,
    End,
    PageUp,
    PageDown,
    ArrowLeft,
    ArrowRight,
    ArrowUp,
    ArrowDown
} SpecialKey_t;

typedef enum
{
    Modifier,
    Special,
    Literal
} KeyType_t;

typedef union
{
    ModifierKey_t modifier;
    SpecialKey_t special;
    char literal;
} KeyValue_t;

typedef struct
{
    KeyValue_t value;
    KeyType_t type;
} Key_t;

static const char *modifier_key_to_string(ModifierKey_t mk)
{
    switch (mk)
    {
    case Mod:
        return ModVarName;
    case Return:
        return "Return";
    case Ctrl:
        return "Ctrl";
    case Shift:
        return "Shift";
    case Alt:
        return "Alt";
    case CapsLock:
        return "Caps_Lock";
    default:
        return "<unknown-mod>";
    }
}

static const char *special_key_to_string(SpecialKey_t sk)
{
    switch (sk)
    {
    case Escape:
        return "Escape";
    case Tab:
        return "Tab";
    case Space:
        return "space";
    case Insert:
        return "Insert";
    case Delete:
        return "Delete";
    case Home:
        return "Home";
    case End:
        return "End";
    case PageUp:
        return "Page_Up";
    case PageDown:
        return "Page_Down";
    case ArrowLeft:
        return "Left";
    case ArrowRight:
        return "Right";
    case ArrowUp:
        return "Up";
    case ArrowDown:
        return "Down";
    default:
        return "<unknown-special>";
    }
}

static const char *key_to_string(const Key_t *key)
{
    switch (key->type)
    {
    case Modifier:
        return modifier_key_to_string(key->value.modifier);
    case Special:
        return special_key_to_string(key->value.special);
    case Literal:
    {
        static char buf[2] = {0};
        buf[0] = key->value.literal;
        return buf;
    }
    default:
        return "<invalid-key>";
    }
}

void print_keys(Key_t **keys)
{
    for (size_t i = 0; keys[i] != NULL; i++)
    {
        printf("%s", key_to_string(keys[i]));
        if (keys[i + 1] != NULL)
            printf("+");
    }
}

#define LITERAL_KEY(c) \
    &(Key_t) { .value = {.literal = (c)}, .type = Literal }
#define MODIFIER_KEY(m) \
    &(Key_t) { .value = {.modifier = (m)}, .type = Modifier }
#define SPECIAL_KEY(s) \
    &(Key_t) { .value = {.special = (s)}, .type = Special }
#define KEYS(...) \
    (Key_t *[]) { __VA_ARGS__, NULL }

#endif
