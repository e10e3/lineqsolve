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

extern fraction* multiply_fractions(fraction*, fraction*);
extern fraction* add_fractions(fraction*, fraction*);
extern bool simplify_fraction(fraction* fraction);
bool are_fractions_equal(fraction*, fraction*);

int get_gcd(const int, const int);
int gcd(int, int);

#endif /* FRACTIONS_H */
