/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/


#include "my.h"

struct dirent **add_entry(struct dirent *entry, struct dirent ***files)
{
    int len = 0;
    struct dirent **tmp = NULL;

    for (; (*files)[len]; len++);
    tmp = malloc(sizeof(struct dirent *) * (len + 2));
    for (int i = 0; i++ < len; tmp[i - 1] = (*files)[i - 1]);
    tmp[len] = entry;
    tmp[len + 1] = NULL;
    free(*files);
    *files = tmp;
    return tmp;
}

static int my_revcmp(char *a, char *b)
{
    return my_strcmp(b, a);
}

static int read_files(DIR *dir, my_lsflags_t *flgs, char **buf, char const *path)
{
    struct dirent **files = malloc(sizeof(struct dirent *));
    int error = 0;

    if (!files)
       return 84;
    *files = NULL;
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir))
        add_entry(entry, &files);
    my_advanced_sort_entry_array(files, my_strcmp);
    flgs->has_r && my_advanced_sort_entry_array(files, my_revcmp);
    for (int i = 0; files[i]; i++)
        error |= read_file(files[i], flgs, buf, path);
    return error;
}

int read_dir(char const *path, my_lsflags_t *flgs, char **buf, bool is_last)
{
    char *ret = NULL;
    DIR *dir = opendir(path);
    int error = 0;

    if (!dir) {
        my_dprintf(2, "ls: cannot access '%s': ", path);
        my_dprintf(2, "No such file or directory\n");
        return 84;
    }
    if (flgs->has_d) {
        my_saprintf(&ret, "", "%s", path);
        add_buffer(buf, ret, my_strlen(ret));
        add_buffer(buf, " ", !is_last);
        free(ret);
        return 0;
    }
    flgs->print_name && add_buffer(buf, (void *)path, my_strlen(path));
    flgs->print_name && add_buffer(buf, ":\n", 2);
    error |= read_files(dir, flgs, buf, path);
    add_buffer(buf, "\n\n", 1 + !is_last);
    return error;
}
