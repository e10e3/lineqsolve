/*
 * Header file for fractions.c
 */

#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <stdlib.h>
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
extern bool are_fractions_equal(const fraction* const, const fraction* const);
extern fraction* invert_fraction(fraction*);

int get_gcd(const int, const int);
int gcd(int, int);

#endif /* FRACTIONS_H */
