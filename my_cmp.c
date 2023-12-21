/*
** EPITECH PROJECT, 2023
** Pool Day 06
** File description:
** Placeholder
*/

#include "my.h"

int my_timecmp(time_t a, char const *str_a, time_t b, char const *str_b)
{
    int ret = (a > b) - (b > a);

    if (ret == 0)
        return my_strcmp(str_a, str_b);
    return (a > b) - (b > a);
}

int my_revtimecmp(time_t a, char const *str_a, time_t b, char const *str_b)
{
    return -1 * my_timecmp(a, str_a, b, str_b);
}

int my_revcmp(char const *a, char const *b)
{
    return my_strcmp(b, a);
}
