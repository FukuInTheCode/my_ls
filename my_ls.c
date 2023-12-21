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

int main(int argc, char **argv)
{
    my_lsflags_t flgs = {false, false, false, false, false, false};
    bool no_dir_arg = false;

    for (int i = 1; i < argc; (!my_strncmp(argv[i++], "-", 1) &&
        (find_flgs(argv[i - 1] + 1, &flgs) || 1)) || (no_dir_arg = true));
    if (no_dir_arg)
        return read_dir("./", &flgs);
    for (int i = 1; i < argc; (my_strncmp("-", argv[i++], 1) ||
        1 == my_strlen(argv[i - 1])) && read_dir(argv[i - 1], &flgs));
    return 0;
}
