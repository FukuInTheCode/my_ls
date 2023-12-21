/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/


#include "my.h"

static int add_other2(char **out, struct stat *s,
    my_lsflags_t *flgs, struct group *grp)
{
    int exp = my_fexpn(s->st_size, 10, NULL) + 1;
    char tmp[1000] = {0};

    for (int i = 0; i++ < flgs->col_gr - my_strlen(grp->gr_name);)
        add_buffer(out, " ", 1);
    my_sprintf(tmp, "%s ", grp->gr_name);
    add_buffer(out, tmp, my_strlen(tmp));
    for (int i = 0; i++ < flgs->col_size - exp; add_buffer(out, " ", 1));
    my_sprintf(tmp, "%lld ", s->st_size) &&
        add_buffer(out, tmp, my_strlen(tmp));
    add_buffer(out, ctime(&s->st_mtime) + 4, 12);
    add_buffer(out, " ", 1);
    return 0;
}

static int add_other(char **out, struct stat *s, my_lsflags_t *flgs)
{
    struct passwd *pwd = getpwuid(s->st_uid);
    struct group *grp = getgrgid(s->st_gid);
    int exp = my_fexpn(s->st_nlink, 10, NULL) + 1;
    char tmp[1000] = {0};

    for (int i = 0; i++ < flgs->col_link - exp; add_buffer(out, " ", 1));
    my_sprintf(tmp, "%lld ", s->st_nlink);
    add_buffer(out, tmp, my_strlen(tmp));
    for (int i = 0; i++ < flgs->col_pw - my_strlen(pwd->pw_name);)
        add_buffer(out, " ", 1);
    my_sprintf(tmp, "%s ", pwd->pw_name);
    add_buffer(out, tmp, my_strlen(tmp));
    add_other2(out, s, flgs, grp);
    return 0;
}

static int add_perm(char **out, struct stat *s, my_lsflags_t *flgs)
{
    S_ISDIR(s->st_mode) && my_saprintf(out, "", "d");
    S_ISLNK(s->st_mode) && my_saprintf(out, "", "l");
    S_ISBLK(s->st_mode) && my_saprintf(out, "", "b");
    S_ISCHR(s->st_mode) && my_saprintf(out, "", "c");
    !S_ISLNK(s->st_mode) && !S_ISDIR(s->st_mode) &&
        !S_ISCHR(s->st_mode) && !S_ISBLK(s->st_mode) &&
        my_saprintf(out, "", "-");
    add_buffer(out, S_IRUSR & s-> st_mode ? "r" : "-", 1);
    add_buffer(out, S_IWUSR & s-> st_mode ? "w" : "-", 1);
    add_buffer(out, S_IXUSR & s-> st_mode ? "x" : "-", 1);
    add_buffer(out, S_IRGRP & s-> st_mode ? "r" : "-", 1);
    add_buffer(out, S_IWGRP & s-> st_mode ? "w" : "-", 1);
    add_buffer(out, S_IXGRP & s-> st_mode ? "x" : "-", 1);
    add_buffer(out, S_IROTH & s-> st_mode ? "r" : "-", 1);
    add_buffer(out, S_IWOTH & s-> st_mode ? "w" : "-", 1);
    add_buffer(out, S_IXOTH & s-> st_mode ? "x " : "- ", 2);
    s->st_mode & S_ISVTX && (*out)[my_strlen(*out) - 2] == 'x' &&
        ((*out)[my_strlen(*out) - 2] = 't');
    s->st_mode & S_ISVTX && (*out)[my_strlen(*out) - 2] == '-' &&
        ((*out)[my_strlen(*out) - 2] = 'T');
    add_other(out, s, flgs);
    return 0;
}

static int file_stat(struct dirent *entry, my_lsflags_t *flgs,
    char **buf, char const *path)
{
    char file_path[1000] = {0};
    struct stat s;
    int error = 0;
    char *out = NULL;
    char lnk_path[1000] = {0};

    my_sprintf(file_path, "%s/%s", path, entry->d_name);
    if (!my_strlen(path) || path[my_strlen(path) - 1] == '/')
        my_sprintf(file_path, "%s%s", path, entry->d_name);
    error |= -84 * lstat(file_path, &s);
    flgs->has_l && add_perm(&out, &s, flgs);
    out && add_buffer(buf, out, my_strlen(out));
    free(out);
    add_buffer(buf, entry->d_name, my_strlen(entry->d_name));
    S_ISLNK(s.st_mode) && flgs->has_l && add_buffer(buf, " -> ", 4);
    S_ISLNK(s.st_mode) && flgs->has_l && readlink(file_path, lnk_path, 1000);
    S_ISLNK(s.st_mode) && flgs->has_l && add_buffer(buf, lnk_path,
        my_strlen(lnk_path));
    return error;
}

int read_file(struct dirent *entry, my_lsflags_t *flgs, char **buf,
    char const *path)
{
    int error = 0;

    if (entry->d_name[0] == '.' && !flgs->has_a && !flgs->has_d)
        return error;
    error |= file_stat(entry, flgs, buf, path);
    !flgs->has_l && add_buffer(buf, " ", 1);
    flgs->has_l && add_buffer(buf, "\n", 1);
    return error;
}
