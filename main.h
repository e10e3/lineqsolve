/**
 * @file main.h
 * @brief Function prototypes for main.c
 * @see main.c
 */

#ifndef MAIN_H
#define MAIN_H

#include "fractions.h"
#include "stddef.h"

size_t count_char_in_string(const char, const char *);
void pp_matrix(fraction **const, const size_t, const size_t);
size_t find_greatest_value_in_column(fraction **const, const size_t,
                                     const size_t);
void subtract_lines_in_place(fraction *const, fraction *const, const size_t);
void multiply_line_in_place(fraction *const, const fraction, const size_t);
void triangularise(fraction **const, const size_t, const size_t);
void print_results(fraction **const, const size_t, const size_t);
void gaussian_elimination(fraction **const, const size_t, const size_t);

#endif /* MAIN_H */
