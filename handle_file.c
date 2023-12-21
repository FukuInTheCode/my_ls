/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/


#include "my.h"

static int file_stat(struct dirent *entry, my_lsflags_t *flgs, char **buf, char const *path)
{
    char file_path[1000] = {0};

    my_sprintf(file_path, "%s/%s", path, entry->d_name);
    (path[my_strlen(path) - 1] == '/') && my_sprintf(file_path, "%s%s", path, entry->d_name);
    my_printf("%s\n", file_path);
    return 0;
}

int read_file(struct dirent *entry, my_lsflags_t *flgs, char **buf, char const *path)
{
    if (entry->d_name[0] == '.' && !flgs->has_a)
        return 0;
    if (flgs->has_l)
        file_stat(entry, flgs, buf, path);
    add_buffer(buf, entry->d_name, my_strlen(entry->d_name));
    add_buffer(buf, " ", 1);
    return 0;
}
