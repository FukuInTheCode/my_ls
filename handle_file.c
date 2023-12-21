/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/


#include "my.h"

int read_file(struct dirent *entry, my_lsflags_t *flgs, char **buf, char const *path)
{
    if (entry->d_name[0] == '.' && !flgs->has_a)
        return 0;
    add_buffer(buf, entry->d_name, my_strlen(entry->d_name));
    add_buffer(buf, " ", 1);
    return 0;
}
