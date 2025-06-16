#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include <stddef.h>
#include <stdio.h>

#define ModVarName "$mod"
#define TermVarName "$term"
#define MenuVarName "$menu"
#define RofiCmdVarName "$rofi_cmd"

typedef struct
{
    const char *name;
    const char *value;
} Variable_t;

void print_variables(const Variable_t vars[], size_t variable_count)
{
    for (size_t i = 0; i < variable_count; i++)
    {
        Variable_t var = vars[i];
        printf("set %s %s\n", var.name, var.value);
    }
}

#endif // __VARIABLES_H__
