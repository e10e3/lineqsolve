#include "fractions.h"

#include <stdlib.h>

void
multiply_fractions(const fraction *const fraction_in1,
                   const fraction *const fraction_in2, fraction *const result)
{
	result->numerator = fraction_in1->numerator * fraction_in2->numerator;
	result->denominator =
	    fraction_in1->denominator * fraction_in2->denominator;
	simplify_fraction(result);
}

void
add_fractions(const fraction *const fraction_in1,
              const fraction *const fraction_in2, fraction *const result)
{
	if (fraction_in1->denominator == fraction_in2->denominator) {
		result->numerator =
		    fraction_in1->numerator + fraction_in2->numerator;
		result->denominator = fraction_in1->denominator;
	} else {
		result->numerator =
		    fraction_in1->numerator * fraction_in2->denominator +
		    fraction_in2->numerator * fraction_in1->denominator;
		result->denominator =
		    fraction_in1->denominator * fraction_in2->denominator;
	}
	simplify_fraction(result);
}

/**
 * Substract fraction2 from fraction1
 */
void
substract_fractions(const fraction *const fraction1,
                    const fraction *const fraction2, fraction *const result)
{
	if (fraction1->denominator == fraction2->denominator) {
		result->numerator = fraction1->numerator - fraction2->numerator;
		result->denominator = fraction1->denominator;
	} else {
		result->numerator =
		    fraction1->numerator * fraction2->denominator -
		    fraction2->numerator * fraction1->denominator;
		result->denominator =
		    fraction1->denominator * fraction2->denominator;
	}
	simplify_fraction(result);
}

/**
 * Comparison function — returns -1, 0, or 1 if a is less, equal or greater
 * compared to b.
 */
int
compare_fractions(const fraction *const f_a, const fraction *const f_b)
{
	long left_side = f_a->numerator * f_b->denominator;
	long right_side = f_b->numerator * f_a->denominator;
	return (left_side < right_side) ? -1 : (left_side > right_side);
}

/**
 * Reduces a given fraction
 * Returns true if the fraction has been reduced, false otherwise
 */
bool
simplify_fraction(fraction *const fraction)
{
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
	/* If the fraction is equal to zero, we chose to force the
	 * denominator to 1 and consider it reduced */
	if (fraction->numerator == 0) {
		fraction->denominator = 1;
		return true;
	}
	int divisor = gcd(fraction->numerator, fraction->denominator);
	if (divisor == 1) {
		return false;
	} else {
		fraction->numerator /= divisor;
		fraction->denominator /= divisor;
		return true;
	}
}

void
invert_fraction(const fraction *const input_frac, fraction *const result)
{
	if (input_frac->numerator == 0) {
		return;
	}
	result->numerator = input_frac->denominator;
	result->denominator = input_frac->numerator;
}

/**
 * Prepare the numbers for GCD calculation
 */
int
gcd(const int first, const int second)
{
	return compute_gcd((first > 0 ? first : -first),
	                   (second > 0 ? second : -second));
}

/**
 * Uses the binary version of the Euclidian algorithm (aka Stein's algorithm)
 */
int
compute_gcd(int first, int second)
{
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
		} else if (first % 2 == 0) {
			first /= 2;
		} else if (second % 2 == 0) {
			second /= 2;
		} else {
			first -= second;
		}
	}
	return first << divisions;
}
