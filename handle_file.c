/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/


#include "my.h"

static int add_perm(char **out, struct stat *s, my_lsflags_t *flgs)
{
    struct passwd *pwd = getpwuid(s->st_uid);
    struct group *grp = getgrgid(s->st_gid);
    int exp = my_fexpn(s->st_size, 10, NULL) + 1;
    char tmp[1000] = {0};

    my_saprintf(out, "", S_ISDIR(s->st_mode) ? "d" : "-");
    add_buffer(out, S_IRUSR & s-> st_mode ? "r" : "-", 1);
    add_buffer(out, S_IWUSR & s-> st_mode ? "w" : "-", 1);
    add_buffer(out, S_IXUSR & s-> st_mode ? "x" : "-", 1);
    add_buffer(out, S_IRGRP & s-> st_mode ? "r" : "-", 1);
    add_buffer(out, S_IWGRP & s-> st_mode ? "w" : "-", 1);
    add_buffer(out, S_IXGRP & s-> st_mode ? "x" : "-", 1);
    add_buffer(out, S_IROTH & s-> st_mode ? "r" : "-", 1);
    add_buffer(out, S_IWOTH & s-> st_mode ? "w" : "-", 1);
    add_buffer(out, S_IXOTH & s-> st_mode ? "x " : "- ", 2);
    my_sprintf(tmp, "%lld %s %s ", s->st_nlink,
        pwd->pw_name, grp->gr_name);
    add_buffer(out, tmp, my_strlen(tmp));
    for (int i = 0; i++ < flgs->col_format - exp; add_buffer(out, " ", 1));
    my_sprintf(tmp, "%lld ", s->st_size) && add_buffer(out, tmp, my_strlen(tmp));
    return 0;
}

static int file_stat(struct dirent *entry, my_lsflags_t *flgs, char **buf, char const *path)
{
    char file_path[1000] = {0};
    struct stat s;
    int error = 0;
    char *out = NULL;

    my_sprintf(file_path, "%s/%s", path, entry->d_name);
    if (path[my_strlen(path) - 1] == '/')
        my_sprintf(file_path, "%s%s", path, entry->d_name);
    error |= -84 * stat(file_path, &s);
    add_perm(&out, &s, flgs);
    add_buffer(buf, out, my_strlen(out));
    free(out);
    return error;
}

int read_file(struct dirent *entry, my_lsflags_t *flgs, char **buf, char const *path)
{
    if (entry->d_name[0] == '.' && !flgs->has_a)
        return 0;
    if (flgs->has_l)
        file_stat(entry, flgs, buf, path);
    add_buffer(buf, entry->d_name, my_strlen(entry->d_name));
    !flgs->has_l && add_buffer(buf, " ", 1);
    flgs->has_l && add_buffer(buf, "\n", 1);
    return 0;
}
