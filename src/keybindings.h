#ifndef __KEYBINDINGS_H__
#define __KEYBINDINGS_H__

#include "keys.h"
#include "variables.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define KEYBIND(desc, keylist, cmd) \
    (Keybind_t) { .description = desc, .keys = keylist, .command = cmd }

typedef struct
{
    const char *description;
    Key_t **keys;         // NULL-terminated
    const char **command; // NULL-terminated
} Keybind_t;

void print_keybind(const Keybind_t *kb)
{
    printf("bindsym ");
    for (size_t i = 0; kb->keys[i] != NULL; i++)
    {
        printf("%s", key_to_string(kb->keys[i]));
        if (kb->keys[i + 1] != NULL)
            printf("+");
    }

    printf(" ");

    for (size_t j = 0; kb->command[j] != NULL; j++)
    {
        printf("%s", kb->command[j]);
        if (kb->command[j + 1] != NULL)
            printf(" ");
    }

    printf("\n");
}

void print_keybinds(const Keybind_t keybinds[], size_t keybind_count)
{
    for (size_t i = 0; i < keybind_count; i++)
    {
        print_keybind(&keybinds[i]);
    }
}

#endif // __KEYBINDINGS_H__
