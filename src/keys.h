#ifndef __KEYS_H__
#define __KEYS_H__

#include "variables.h"
#define SuperKey "Mod4"
#define AltKey "Mod1"

typedef enum { Mod, Return, Ctrl, Alt, Shift, CapsLock } ModifierKey_t;

typedef enum {
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

typedef enum { Modifier, Special, Literal } KeyType_t;

typedef union {
  ModifierKey_t modifier;
  SpecialKey_t special;
  char literal;
} KeyValue_t;

typedef struct {
  KeyValue_t value;
  KeyType_t type;
} Key_t;

static const char *modifier_key_to_string(ModifierKey_t mk) {
  switch (mk) {
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

static const char *special_key_to_string(SpecialKey_t sk) {
  switch (sk) {
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

static const char *key_to_string(const Key_t *key) {
  switch (key->type) {
  case Modifier:
    return modifier_key_to_string(key->value.modifier);
  case Special:
    return special_key_to_string(key->value.special);
  case Literal: {
    static char buf[2] = {0};
    buf[0] = key->value.literal;
    return buf;
  }
  default:
    return "<invalid-key>";
  }
}

void print_keys(Key_t **keys) {
  for (size_t i = 0; keys[i] != NULL; i++) {
    printf("%s", key_to_string(keys[i]));
    if (keys[i + 1] != NULL)
      printf("+");
  }
}

#define LITERAL(c)                                                             \
  &(Key_t) { .value = {.literal = (c)}, .type = Literal }

static Key_t _Mod = {.value.modifier = Mod, .type = Modifier};
static Key_t _Return = {.value.modifier = Return, .type = Modifier};
static Key_t _Ctrl = {.value.modifier = Ctrl, .type = Modifier};
static Key_t _Alt = {.value.modifier = Alt, .type = Modifier};
static Key_t _Shift = {.value.modifier = Shift, .type = Modifier};
static Key_t _CapsLock = {.value.modifier = CapsLock, .type = Modifier};
#define Mod (&_Mod)
#define Return (&_Return)
#define Ctrl (&_Ctrl)
#define Alt (&_Alt)
#define Shift (&_Shift)
#define CapsLock (&_CapsLock)

static Key_t _Escape = {.value.special = Escape, .type = Special};
static Key_t _Tab = {.value.special = Tab, .type = Special};
static Key_t _Space = {.value.special = Space, .type = Special};
static Key_t _Insert = {.value.special = Insert, .type = Special};
static Key_t _Delete = {.value.special = Delete, .type = Special};
static Key_t _Home = {.value.special = Home, .type = Special};
static Key_t _End = {.value.special = End, .type = Special};
static Key_t _PageUp = {.value.special = PageUp, .type = Special};
static Key_t _PageDown = {.value.special = PageDown, .type = Special};
static Key_t _ArrowLeft = {.value.special = ArrowLeft, .type = Special};
static Key_t _ArrowRight = {.value.special = ArrowRight, .type = Special};
static Key_t _ArrowUp = {.value.special = ArrowUp, .type = Special};
static Key_t _ArrowDown = {.value.special = ArrowDown, .type = Special};
#define Escape (&_Escape)
#define Tab (&_Tab)
#define Space (&_Space)
#define Insert (&_Insert)
#define Delete (&_Delete)
#define Home (&_Home)
#define End (&_End)
#define PageUp (&_PageUp)
#define PageDown (&_PageDown)
#define ArrowLeft (&_ArrowLeft)
#define ArrowRight (&_ArrowRight)
#define ArrowUp (&_ArrowUp)
#define ArrowDown (&_ArrowDown)

#endif
