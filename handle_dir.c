/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/


#include "my.h"

int read_dir(char const *path, my_lsflags_t *flgs, char **buf)
{
    if (flgs->has_d)
        add_buffer(buf, (void *)path, my_strlen(path));

    add_buffer(buf, "  ", 2);
    return 0;
}
