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

extern fraction* multiply_fractions(const fraction* const, const fraction* const);
extern fraction* add_fractions(const fraction* const, const fraction* const);
extern fraction* substract_fractions(const fraction* const, const fraction* const);
extern bool simplify_fraction(fraction* fraction);
extern fraction* invert_fraction(fraction*);
int compare_fractions(const fraction *const, const fraction *const);

/* Internal functions */
int get_gcd(const int, const int);
int gcd(int, int);

#endif /* FRACTIONS_H */
