/*
 * Header file for fractions.c
 */

#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <stdbool.h>

struct fraction {
	int numerator;
	int denominator;
};

typedef struct fraction fraction;

void multiply_fractions(const fraction *const, const fraction *const,
                        fraction *const);
void add_fractions(const fraction *const, const fraction *const,
                   fraction *const);
void substract_fractions(const fraction *const, const fraction *const,
                         fraction *const);
int compare_fractions(const fraction *const, const fraction *const);
bool simplify_fraction(fraction *const);
void invert_fraction(const fraction *const, fraction *const);

/* Internal functions */
int gcd(const int, const int);
int compute_gcd(int, int);

#endif /* FRACTIONS_H */
