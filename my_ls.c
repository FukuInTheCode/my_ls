/*
** EPITECH PROJECT, 2023
** my_ls main.c
** File description:
** Placeholder
*/

#include "my.h"

static int is_valid_flgs(char c)
{
    for (int i = 0; ls_flgs[i].s; i++)
        if (!my_strncmp(ls_flgs[i].s, &c, 1))
            return 1;
    return 0;
}

static int find_flgs(char const *arg, my_lsflags_t *flgs)
{
    for (int i = 0; is_valid_flgs(arg[i]); i++)
        for (int j = 0; ls_flgs[j++].s; !my_strncmp(arg + i,
            ls_flgs[j - 1].s, 1) && ls_flgs[j - 1].f(flgs));
    return 0;
}

static char **add_file(char const *path, char ***files)
{
    int len = 0;
    char **tmp = NULL;

    for (; (*files)[len]; len++);
    tmp = malloc(sizeof(char *) * (len + 2));
    for (int i = 0; i++ < len; tmp[i - 1] = (*files)[i - 1]);
    tmp[len] = (void *)path;
    tmp[len + 1] = NULL;
    free(*files);
    *files = tmp;
    return tmp;
}

static int my_cmp(char const *a, char const *b)
{
    return my_strcmp(a, b);
}

static int my_revcmp(char const *a, char const *b)
{
    return my_strcmp(b, a);
}

int main(int argc, char **argv)
{
    my_lsflags_t flgs = {false, false, false, false, false, false};
    bool no_dir_arg = true;
    char *buffer = malloc(1);
    char **files = malloc(sizeof(char *));

    if (!buffer || !files)
        return 84;
    *buffer = 0;
    *files = NULL;
    for (int i = 1; i < argc; i++)
        (!my_strncmp(argv[i], "-", 1) && 1 != my_strlen(argv[i]) &&
            (find_flgs(argv[i] + 1, &flgs) || 1)) || (no_dir_arg = false);
    if (no_dir_arg || argc == 1)
        read_dir(".", &flgs, &buffer);
    for (int i = 1; i < argc; (my_strncmp("-", argv[i++], 1) ||
        1 == my_strlen(argv[i - 1])) && add_file(argv[i - 1], &files));
    (!flgs.has_r && (my_advanced_sort_word_array(files, my_cmp) || 1)) ||
        my_advanced_sort_word_array(files, my_revcmp);
    for (int i = 0; files[i]; read_dir(files[i++], &flgs, &buffer));
    my_printf("%s\n", buffer);
    free(buffer);
    return 0;
}
