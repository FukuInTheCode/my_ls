/*
** EPITECH PROJECT, 2023
** my_ls main.c
** File description:
** Placeholder
*/

#include "my.h"
#include <dirent.h>

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
    char *tmp_path = malloc(my_strlen(path) + 1);

    for (int i = 0; path[i++]; tmp_path[i - 1] = path[i - 1]);
    tmp_path[my_strlen(path)] = 0;
    for (; (*files)[len]; len++);
    tmp = malloc(sizeof(char *) * (len + 2));
    for (int i = 0; i++ < len; tmp[i - 1] = (*files)[i - 1]);
    tmp[len] = (void *)tmp_path;
    tmp[len + 1] = NULL;
    free(*files);
    *files = tmp;
    return tmp;
}

static int inter_find_file(my_lsflags_t *flgs, char *file, char ***files)
{
    DIR *dirp = opendir(file);
    char tmp_path[1000] = {0};
    struct dirent *entry = NULL;
    int error = 0;
    struct stat s;

    add_file(file, files);
    if (!flgs->has_rmaj || !dirp || flgs->has_d)
        return error;
    for (entry = readdir(dirp); entry; entry = readdir(dirp)) {
        my_sprintf(tmp_path, file[my_strlen(file) - 1] == '/' ?
            "%s%s" : "%s/%s", file, entry->d_name);
        lstat(tmp_path, &s);
        if (S_ISDIR(s.st_mode) && entry->d_name[0] != '.')
            error |= inter_find_file(flgs, tmp_path, files);
    }
    closedir(dirp);
    return error;
}

static int find_files(my_lsflags_t *flgs, char **s[3], int argc)
{
    char **buffer = s[0];
    char **argv = s[1];
    char **files = s[2];
    int len = 0;
    int error = 0;

    for (int i = 1; i < argc; i++)
        (my_strncmp("-", argv[i], 1) ||
        1 == my_strlen(argv[i])) && inter_find_file(flgs, argv[i], &files);
    (!flgs->has_r && (my_advanced_sort_word_array(files, my_strcmp) || 1)) ||
        my_advanced_sort_word_array(files, my_revcmp);
    for (; files[len]; len++);
    (len <= 1) && (flgs->is_one = true);
    (len > 1) && (flgs->print_name = true);
    for (int i = 0; files[i]; i++)
        error |= read_dir(files[i], flgs, buffer, files[i + 1] == NULL);
    return error;
}

int my_free(void *ptr)
{
    free(ptr);
    return 0;
}

int main(int argc, char **argv)
{
    my_lsflags_t flgs = {false, false, false, false,
        false, false, false, false, 0, 0, 0, 0, 0};
    bool no_dir_arg = true;
    char *buffer = malloc(1);
    char **files = malloc(sizeof(char *));
    int error = 0;

    if (!buffer || !files)
        return 84;
    *buffer = 0;
    *files = NULL;
    for (int i = 1; i < argc; i++)
        (!my_strncmp(argv[i], "-", 1) && 1 != my_strlen(argv[i]) &&
            (find_flgs(argv[i] + 1, &flgs) || 1)) || (no_dir_arg = false);
    (no_dir_arg || argc == 1) && inter_find_file(&flgs, ".", &files);
    error |= find_files(&flgs, (char **[3]){ &buffer, argv, files }, argc);
    my_nprintf(my_strlen(buffer), "%s", buffer);
    my_free(buffer);
    return error;
}
