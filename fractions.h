/**
 * @file fractions.h
 * @brief Definitions for fractions.c
 * @see fractions.c
 */

#ifndef FRACTIONS_H
#define FRACTIONS_H

#include <stdbool.h>

/**
 * @brief A structure to store fractions.
 *
 * A fraction is written in the form \f$\frac{a}{b}\f$, where \f$a\f$ is the
 * numerator of the fraction and \f$b\f$ its denominator.
 *
 * Since negative signs cancel each other out, storing one for the whole
 * fraction is enough.
 */
/*
 * This implementation is sightly less memory-efficient than storing signed
 * integers, but it allows for a) more precision and b) less integer overflow
 * problems.
 */
struct fraction {
	/** Whether the fraction is negative. This is effectively a sign byte.
	 */
	bool negative;
	/** The numerator of the fraction */
	unsigned int numerator;
	/** The denominator of the fraction */
	unsigned int denominator;
};

/**
 * @brief Definition of a type from the fraction structure.
 * @see struct fraction
 */
typedef struct fraction fraction;

void multiply_fractions(const fraction *const, const fraction *const,
                        fraction *const);
void substract_fractions(const fraction *const, const fraction *const,
                         fraction *const);
int compare_fractions(const fraction *const, const fraction *const);
bool simplify_fraction(fraction *const);
void invert_fraction(const fraction *const, fraction *const);
char fraction_sign_as_character(const fraction *const);

#endif /* FRACTIONS_H */
