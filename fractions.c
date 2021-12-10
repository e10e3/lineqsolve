#include "fractions.h"

fraction* multiply_fractions(fraction* fraction1, fraction* fraction2) {
	fraction *result = (fraction*)malloc(sizeof(fraction));
	result->numerator = fraction1->numerator * fraction2->numerator;
	result->denominator = fraction1->numerator * fraction2->denominator;
	simplify_fraction(result);
	return result;
}

fraction* add_fractions(fraction* fraction1, fraction* fraction2) {
	fraction* result = (fraction*)malloc(sizeof(fraction));
	if (fraction1->denominator == fraction2->denominator) {
		result->numerator = fraction1->numerator + fraction2->numerator;
		result->denominator = fraction1->denominator;
	} else {
		result->numerator =
			fraction1->numerator * fraction2->denominator
			+ fraction2->numerator * fraction1->denominator;
		result->denominator =
			fraction1->denominator * fraction2->denominator;
	}
	simplify_fraction(result);
	return result;
}

/**
 * Reduces a given fraction
 * Returns true if the fraction has been reduced, false otherwise
 */
bool simplify_fraction(fraction* fraction) {
	if ((fraction->numerator < 0) && (fraction->denominator < 0)) {
		fraction->numerator *= -1;
		fraction->denominator *= -1;
	}
	if ((fraction->numerator > 0) && (fraction->denominator < 0)) {
	/* Get the negative sign on the numerator, because I find it
	 * "cleaner" this way */
		fraction->numerator *= -1;
		fraction->denominator *= -1;
	}
	int divisor = get_gcd(fraction->numerator, fraction->denominator);
	if (divisor == 1) {
		return false;
	} else {
		fraction->numerator /= divisor;
		fraction->denominator /= divisor;
		return true;
	}
}

/**
 * Prepare the numbers for GCD calculation
 */
int get_gcd(const int first, const int second) {
	return gcd(
			(first > 0 ? first : -first),
			(second > 0 ? second : second));
}

/**
 * Uses the binary version of the Euclidian algorithm (aka Stein's algorithm)
 */
int gcd(int first, int second/*, int divisions*/) {
	int temp;
	int divisions = 0;
	while (second != 0) {
		if (first < second) {
			temp = second;
			second = first;
			first = temp;
		}
		if (first % 2 == 0 && second % 2 == 0) {
			first /= 2;
			second /= 2;
			divisions++;
		} else  if (first % 2 == 0) {
			first /= 2;
		} else if (second % 2 == 0) {
			second /= 2;
		} else {
			first -= second;
		}
	}
	return first << divisions;
}
