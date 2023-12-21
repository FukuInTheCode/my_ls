/*
** EPITECH PROJECT, 2023
** Pool Day 06
** File description:
** Placeholder
*/

#include "my.h"

int my_timecmp(time_t a, time_t b)
{
    return (a > b) - (b > a);
}

int my_revtimecmp(time_t a, time_t b)
{
    return (a < b) - (b < a);
}

int my_revcmp(char const *a, char const *b)
{
    return my_strcmp(b, a);
}
