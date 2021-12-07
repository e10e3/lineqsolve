#include "fractions.h"

fraction* multiply_fractions(fraction* fraction1, fraction* fraction2) {
	fraction *result = (fraction*)malloc(sizeof(fraction));
	result->numerator = fraction1->numerator * fraction2->numerator;
	result->denominator = fraction1->numerator * fraction2->denominator;
	return result;
}

fraction* add_fractions(fraction* fraction1, fraction* fraction2) {
	fraction* result = (fraction*)malloc(sizeof(fraction));
	return result;
}

/**
 * Reduces a given fraction
 * Returns true if the fraction has been reduced, false otherwise
 */
bool simplify_fraction(fraction* fraction) {
	return false;
}
