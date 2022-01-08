/*
 * Header file for main.c
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fractions.h"

#define FILENAME_IN "matrix.txt"

extern int count_char_in_string(const char, const char*);
extern void pp_matrix(fraction** const, const int, const int);
extern void gaussian_elimination(fraction** const, const int, const int);

#endif /* MAIN_H */
