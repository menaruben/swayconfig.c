#include "keybindings.h"
#include "helpers.h"
#include "modes.h"
#include "variables.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*
    this is a sample of my own minimal sway config file

    i am using this to generate a sway config file because i dont enjoy
    the normal way of writing sway config files and i want to have the ability
    to maybe add some logic to my sway config in the future.

    there are some things that are not implemented yet, like
    - autostart / top level commands (see main where i hardcode some commands)
    - input block to set keyboard layout, etc...
    - and A LOT more...

    i will probably not add everything that is possible in a sway config file but
    just the things that i use on a daily basis. if you want to add something
    please open an issue or a pull request on github. :)

    happy swaying! :3
*/

#define DefaultModeName "default"
#define ResizeModeName "resize"

// Variables
static const Variable_t variables[] = {
    {.name = ModVarName, .value = SuperKey},
    {.name = TermVarName, .value = "kitty"},
    {.name = RofiCmdVarName, .value = "rofi -terminal '$term'"},
    {.name = MenuVarName,
     .value = "$rofi_cmd -show combi -combi-modes drun#run -modes combi"},
};

static const size_t variable_count = sizeof(variables) / sizeof(Variable_t);

// Keybind command arrays
static const char *cmd_start_terminal[] = {"exec", TermVarName, NULL};
static const char *cmd_sway_reload[] = {"reload", NULL};
static const char *cmd_sway_exit[] = {"exit", NULL};
static const char *cmd_open_firefox[] = {"exec", "firefox", NULL};
static const char *cmd_flameshot_gui[] = {"exec", "flameshot", "gui", NULL};
static const char *cmd_kill_focused_window[] = {"kill", NULL};
static const char *cmd_start_launcher[] = {"exec", MenuVarName, NULL};
static const char *cmd_mode_default[] = {"mode", DefaultModeName, NULL};
static const char *cmd_mode_resize[] = {"mode", ResizeModeName, NULL};

// Keybinds as variables, so that we can potentionally reuse them later in other
// modes...
static const Keybind_t kb_startTerminal =
    KEYBIND("Start terminal", KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Return)),
            cmd_start_terminal);

static const Keybind_t kb_startFirefox =
    KEYBIND("Open firefox browser",
            KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Shift), LITERAL_KEY('b')),
            cmd_open_firefox);

static const Keybind_t kb_flameshot_gui =
    KEYBIND("Takes a screenshot of selected area",
            KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Shift), LITERAL_KEY('s')),
            cmd_flameshot_gui);

static const Keybind_t kb_reload_sway =
    KEYBIND("Reload sway config",
            KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Shift), LITERAL_KEY('c')),
            cmd_sway_reload);

static const Keybind_t kb_exit_sway =
    KEYBIND("Exit/logout of sway session",
            KEYS(MODIFIER_KEY(Mod), LITERAL_KEY('l')), cmd_sway_exit);

static const Keybind_t kb_kill_window =
    KEYBIND("Kill the focused window",
            KEYS(MODIFIER_KEY(Mod), MODIFIER_KEY(Shift), LITERAL_KEY('q')),
            cmd_kill_focused_window);

static const Keybind_t kb_start_launcher =
    KEYBIND("Start application launcher",
            KEYS(MODIFIER_KEY(Mod), LITERAL_KEY('d')), cmd_start_launcher);

static const Keybind_t kb_mode_resize =
    KEYBIND("Switches to resize mode",
            KEYS(MODIFIER_KEY(Mod), LITERAL_KEY('r')), cmd_mode_resize);

static const Keybind_t kb_mode_default = KEYBIND(
    "Switches to default mode", KEYS(SPECIAL_KEY(Escape)), cmd_mode_default);

static const Keybind_t kb_focus_left = MOVE_FOCUS(ArrowLeft, "left");
static const Keybind_t kb_focus_right = MOVE_FOCUS(ArrowRight, "right");
static const Keybind_t kb_focus_up = MOVE_FOCUS(ArrowUp, "up");
static const Keybind_t kb_focus_down = MOVE_FOCUS(ArrowDown, "down");

static const Keybind_t kb_move_left = MOVE_DIRECTION(ArrowLeft, "left");
static const Keybind_t kb_move_down = MOVE_DIRECTION(ArrowDown, "down");
static const Keybind_t kb_move_up = MOVE_DIRECTION(ArrowUp, "up");
static const Keybind_t kb_move_right = MOVE_DIRECTION(ArrowRight, "right");

static const Keybind_t kb_switch_ws_1 = SWITCH_WORKSPACE('1', "1");
static const Keybind_t kb_switch_ws_2 = SWITCH_WORKSPACE('2', "2");
static const Keybind_t kb_switch_ws_3 = SWITCH_WORKSPACE('3', "3");
static const Keybind_t kb_switch_ws_4 = SWITCH_WORKSPACE('4', "4");
static const Keybind_t kb_switch_ws_5 = SWITCH_WORKSPACE('5', "5");
static const Keybind_t kb_switch_ws_6 = SWITCH_WORKSPACE('6', "6");
static const Keybind_t kb_switch_ws_7 = SWITCH_WORKSPACE('7', "7");
static const Keybind_t kb_switch_ws_8 = SWITCH_WORKSPACE('8', "8");
static const Keybind_t kb_switch_ws_9 = SWITCH_WORKSPACE('9', "9");
static const Keybind_t kb_switch_ws_0 = SWITCH_WORKSPACE('0', "10");

static const Keybind_t kb_move_ws_1 = MOVE_TO_WORKSPACE('1', "1");
static const Keybind_t kb_move_ws_2 = MOVE_TO_WORKSPACE('2', "2");
static const Keybind_t kb_move_ws_3 = MOVE_TO_WORKSPACE('3', "3");
static const Keybind_t kb_move_ws_4 = MOVE_TO_WORKSPACE('4', "4");
static const Keybind_t kb_move_ws_5 = MOVE_TO_WORKSPACE('5', "5");
static const Keybind_t kb_move_ws_6 = MOVE_TO_WORKSPACE('6', "6");
static const Keybind_t kb_move_ws_7 = MOVE_TO_WORKSPACE('7', "7");
static const Keybind_t kb_move_ws_8 = MOVE_TO_WORKSPACE('8', "8");
static const Keybind_t kb_move_ws_9 = MOVE_TO_WORKSPACE('9', "9");
static const Keybind_t kb_move_ws_0 = MOVE_TO_WORKSPACE('0', "10");

static const Keybind_t kb_resize_shrink_left =
    RESIZE_WINDOW(ArrowLeft, RESIZE_SHRINK, RESIZE_WINDOW_WIDTH);

static const Keybind_t kb_resize_grow_down =
    RESIZE_WINDOW(ArrowDown, RESIZE_GROW, RESIZE_WINDOW_HEIGHT);

static const Keybind_t kb_resize_shrink_up =
    RESIZE_WINDOW(ArrowUp, RESIZE_SHRINK, RESIZE_WINDOW_HEIGHT);

static const Keybind_t kb_resize_grow_right =
    RESIZE_WINDOW(ArrowRight, RESIZE_GROW, RESIZE_WINDOW_WIDTH);

// modes
static const Keybind_t *defaultModeKeybinds[] = {
    &kb_startTerminal,
    &kb_startFirefox,
    &kb_flameshot_gui,
    &kb_reload_sway,
    &kb_exit_sway,
    &kb_kill_window,
    &kb_start_launcher,
    &kb_mode_resize,
    &kb_focus_left,
    &kb_focus_right,
    &kb_focus_up,
    &kb_focus_down,
    &kb_move_left,
    &kb_move_down,
    &kb_move_up,
    &kb_move_right,
    &kb_switch_ws_1,
    &kb_switch_ws_2,
    &kb_switch_ws_3,
    &kb_switch_ws_4,
    &kb_switch_ws_5,
    &kb_switch_ws_6,
    &kb_switch_ws_7,
    &kb_switch_ws_8,
    &kb_switch_ws_9,
    &kb_switch_ws_0,
    &kb_move_ws_1,
    &kb_move_ws_2,
    &kb_move_ws_3,
    &kb_move_ws_4,
    &kb_move_ws_5,
    &kb_move_ws_6,
    &kb_move_ws_7,
    &kb_move_ws_8,
    &kb_move_ws_9,
    &kb_move_ws_0,
    NULL,
};

static const Mode_t defaultMode = {
    .name = DefaultModeName,
    .keybinds = defaultModeKeybinds,
};

// resize mode
static const Keybind_t *resizeModeKeybinds[] = {
    &kb_mode_default,
    &kb_resize_shrink_left,
    &kb_resize_grow_down,
    &kb_resize_shrink_up,
    &kb_resize_grow_right,
    NULL,
};

static const Mode_t resizeMode = {
    .name = ResizeModeName,
    .keybinds = resizeModeKeybinds,
};

static const Mode_t *modes[] = {
    &defaultMode,
    &resizeMode,
    NULL,
};

static const size_t mode_count = sizeof(modes) / sizeof(Mode_t *);

int main(void)
{
    print_variables(variables, variable_count);
    print_modes(modes, mode_count);

    // run waybar
    printf("exec_always sh -c 'pkill waybar; waybar >/tmp/waybar.log 2>&1 &'\n");

    // set wallpaper
    printf("exec_always swaybg -i ~/Downloads/asa.jpg -m fill\n");
    return 0;
}
