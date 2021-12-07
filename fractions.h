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

#endif /* FRACTIONS_H */
