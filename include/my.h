/*
** EPITECH PROJECT, 2023
** MY_H
** File description:
** Placeholder
*/

#ifndef MY_H
    #define MY_H
    #include <stdio.h>
    #include <unistd.h>
    #include <stdint.h>
    #include <time.h>
    #include <limits.h>
    #include <stdarg.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <math.h>
    #include <stdlib.h>

    #include <criterion/criterion.h>
    #include <criterion/redirect.h>

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <SFML/Config.h>
    #include <SFML/GPUPreference.h>
    #include <SFML/Network.h>
    #include <SFML/OpenGL.h>
    #include <SFML/System.h>
    #include <SFML/Window.h>

    #include "../lib/my_printf/include/my.h"

typedef int(*func)();

typedef struct {
    bool has_a;
    bool has_l;
    bool has_rmaj;
    bool has_d;
    bool has_r;
    bool has_tmin;
} my_lsflags_t;

typedef struct {
    char *s;
    func f;
} my_lsstruct_t;

int my_strncmp(char const *, char const *, int);
int my_strcmp(char const *, char const *);
int my_advanced_sort_word_array(char **, int(*cmp)());
int read_dir(char const *, my_lsflags_t *, char **);

int l_flag_f(my_lsflags_t *);
int d_flag_f(my_lsflags_t *);

static my_lsstruct_t const ls_flgs[] = {
//    {"a", a_flag_f},
    {"l", l_flag_f},
//    {"rmaj", a_flgs_f},
    {"d", d_flag_f},
//    {"r", a_flgs_f},
//    {"tmin", a_flgs_f},
    {NULL, NULL}
};

#endif
