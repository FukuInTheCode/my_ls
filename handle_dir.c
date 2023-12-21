/*
** EPITECH PROJECT, 2023
** handle_dir.c
** File description:
** Placeholder
*/

#include "lib/my_printf/include/my.h"
#include "my.h"

static struct dirent **add_entry(struct dirent *entry, struct dirent ***files)
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

static int inside_loop(my_lsflags_t *flgs, char complete_path[1000],
    struct dirent *file)
{
    struct stat s;
    int error = lstat(complete_path, &s);
    struct passwd *pwd = getpwuid(s.st_uid);
    struct group *grp = getgrgid(s.st_gid);
    int exp = my_fexpn(s.st_size, 10, NULL) + 1;

    flgs->total_blck +=
        s.st_blocks / 2 * (file->d_name[0] != '.' || flgs->has_a);
    (exp > flgs->col_size) && (flgs->col_size = exp);
    exp = my_fexpn(s.st_nlink, 10, NULL) + 1;
    (exp > flgs->col_link) && (flgs->col_link = exp);
    (my_strlen(pwd->pw_name) > flgs->col_pw) &&
        (flgs->col_pw = my_strlen(pwd->pw_name));
    (my_strlen(grp->gr_name) > flgs->col_gr) &&
        (flgs->col_gr = my_strlen(grp->gr_name));
    return error;
}

static int find_col_format(struct dirent **files, my_lsflags_t *flgs,
    char const *path)
{
    char complete_path[1000] = {0};
    int error = 0;

    flgs->col_size = 0;
    flgs->col_gr = 0;
    flgs->col_pw = 0;
    flgs->col_link = 0;
    flgs->total_blck = 0;
    for (int i = 0; files[i]; i++) {
        my_sprintf(complete_path, "%s/%s", path, files[i]->d_name);
        if (!my_strlen(path) || path[my_strlen(path) - 1] == '/')
            my_sprintf(complete_path, "%s%s", path, files[i]->d_name);
        error |= inside_loop(flgs, complete_path, files[i]);
    }
    return error;
}

static int read_files2(my_lsflags_t *flgs, struct dirent **files,
    char const *path, char **buf)
{
    int error = 0;
    char tmp[1000] = {0};

    my_advanced_sort_entry_array(files, my_strcmp);
    flgs->has_r && my_advanced_sort_entry_array(files, my_revcmp);
    flgs->has_tmin && my_advanced_sort_entry_array2(files,
        my_revtimecmp, path);
    flgs->has_tmin &&
        flgs->has_r && my_advanced_sort_entry_array2(files, my_timecmp, path);
    find_col_format(files, flgs, path);
    (flgs->has_l) && my_sprintf(tmp, "total %lld\n", flgs->total_blck) &&
        add_buffer(buf, tmp, my_strlen(tmp));
    return error;
}

static int read_files(DIR *dir, my_lsflags_t *flgs, char **buf,
    char const *path)
{
    struct dirent **files = malloc(sizeof(struct dirent *));
    int error = 0;

    if (!files)
        return 84;
    *files = NULL;
    for (struct dirent *entry = readdir(dir); entry; entry = readdir(dir))
        add_entry(entry, &files);
    read_files2(flgs, files, path, buf);
    for (int i = 0; files[i]; i++)
        error |= read_file(files[i], flgs, buf, path);
    free(files);
    return error;
}

static int handle_d_flag(my_lsflags_t *flgs, char const *path, bool is_last,
    char **buf)
{
    char ret[1000] = {0};
    struct dirent self = {0, 0, 0, 0, {0}};
    struct dirent *self_arr[] = {&self, NULL};

    !flgs->has_l && my_snprintf(ret, my_strlen(path) +
        2 * !is_last, "%s  ", path);
    !flgs->has_l && add_buffer(buf, ret, my_strlen(ret));
    for (int i = 0; i++ < my_strlen(path); self.d_name[i - 1] = path[i - 1]);
    flgs->has_l && find_col_format(self_arr, flgs, "");
    flgs->has_l && read_file(&self, flgs, buf, "");
    !flgs->has_l && add_buffer(buf, "\n", is_last);
    return 0;
}

int read_dir(char const *path, my_lsflags_t *flgs, char **buf, bool is_last)
{
    DIR *dir = opendir(path);
    int error = 0;

    !dir && my_dprintf(2, "ls: cannot access '%s': ", path);
    !dir && my_dprintf(2, "No such file or directory\n");
    if (!dir)
        return 84;
    if (flgs->has_d)
        return handle_d_flag(flgs, path, is_last, buf);
    flgs->print_name && add_buffer(buf, (void *)path, my_strlen(path));
    flgs->print_name && add_buffer(buf, ":\n", 2);
    error |= read_files(dir, flgs, buf, path);
    add_buffer(buf, "\n\n", 1 + !is_last && !flgs->has_l);
    return error;
}
