/*
** EPITECH PROJECT, 2023
** Pool Day 10
** File description:
** Placeholder
*/

#include "include/my.h"

static void my_cmp(struct dirent **tab, int i1, int i2, int cmp)
{
    struct dirent *tmp = NULL;

    if (cmp < 1)
        return;
    tmp = tab[i1];
    tab[i1] = tab[i2];
    tab[i2] = tmp;
}

int my_advanced_sort_entry_array(struct dirent **tab, int(*cmp)())
{
    for (int i = 0; tab[i]; i++)
        for (int j = 1; tab[j]; j++)
            my_cmp(tab, j - 1, j, cmp(tab[j - 1]->d_name, tab[j]->d_name));
    return 0;
}

int my_advanced_sort_entry_array2(struct dirent **tab,
    int(*cmp)(), char const *from)
{
    struct stat s1;
    struct stat s2;
    char path1[1000] = {0};
    char path2[1000] = {0};

    for (int i = 0; tab[i]; i++) {
        for (int j = 1; tab[j]; j++) {
            my_sprintf(path1, "%s/%s", from, tab[j - 1]->d_name);
            (from[my_strlen(from) - 1] == '/') &&
                my_sprintf(path1, "%s%s", from, tab[j - 1]->d_name);
            my_sprintf(path2, "%s/%s", from, tab[j]->d_name);
            (from[my_strlen(from) - 1] == '/') &&
                my_sprintf(path2, "%s%s", from, tab[j]->d_name);
            lstat(path1, &s1);
            lstat(path2, &s2);
            my_cmp(tab, j - 1, j, cmp(s1.st_mtime, tab[j - 1]->d_name, s2.st_mtime, tab[j]->d_name));
        }
    }
    return 0;
}
