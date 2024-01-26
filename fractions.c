/**
 * @file fractions.c
 * @brief Implementation of mathematical operations for fractions.
 *
 * Most functions operate on @ref fraction structures.
 *
 * @see fractions.h
 */
#include "fractions.h"

#include <stdlib.h>

/* -- Helper functions -- */

/**
 * @brief Gives the GCD of two _positive_ integers.
 *
 * Uses the binary version of the Euclidian algorithm (aka Stein's algorithm)
 *
 * @param[in] first One of the integers to compute the GCD of.
 * @param[in] second One of the integers to compute the GCD of.
 *
 * @return The GCD of its inputs.
 *
 * @see gcd() for a general version.
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

/**
 * @brief Gives the GCD of two integers
 *
 * Computes the greatest commom divisor (GCD) of any two integers.
 *
 * Calls @ref compute_gcd with the absolute value of its arguments.
 *
 * @param[in] first One of the integers to compute the GCD of.
 * @param[in] second One of the integers to compute the GCD of.
 *
 * @return The GCD of its inputs.
 */
int
gcd(const int first, const int second)
{
	return compute_gcd((first > 0 ? first : -first),
	                   (second > 0 ? second : -second));
}

/* -- Arithmetic functions -- */

/**
 * @brief Multiplies two fractions together.
 *
 * The result of the multiplication is stored in simplified form.
 *
 * @param[in] fraction_in1 The product's first term.
 * @param[in] fraction_in2 The product's second term.
 * @param[out] result Where to store the product's result.
 */
void
multiply_fractions(const fraction *const fraction_in1,
                   const fraction *const fraction_in2, fraction *const result)
{
	result->numerator = fraction_in1->numerator * fraction_in2->numerator;
	result->denominator =
	    fraction_in1->denominator * fraction_in2->denominator;
	simplify_fraction(result);
}

/**
 * @brief Adds two fractions together.
 *
 * The result of the addition is stored in simplified form.
 *
 * @param[in] fraction_in1 The sum's first term.
 * @param[in] fraction_in2 The sum's second term.
 * @param[out] result Where to store the sum's result.
 */
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
 * @brief Substract a fraction to another.
 *
 * Performs `fraction1` - `fraction2`.
 *
 * The result of the substration is stored in simplified form.
 *
 * @param[in] fraction1 The substraction's first termi (the fraction being
 * substracted from).
 * @param[in] fraction2 The substraction's second term (the fraction being
 * substracted).
 * @param[out] result Where to store the substration's result.
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
 * @brief Compares two fractions
 *
 * Performs a comparison of two fractions, indicating the result in
 * `strcmp`-style.
 *
 * Its return value is -1, 0, or 1 if fraction a is respectively less, equal or
 * greater compared to fraction b.
 *
 * @param[in] f_a The first fraction to compare.
 * @param[in] f_b The second fraction to compare.
 *
 * @return The ordering of `f_a` and `f_b` as an integer.
 */
int
compare_fractions(const fraction *const f_a, const fraction *const f_b)
{
	long left_side = f_a->numerator * f_b->denominator;
	long right_side = f_b->numerator * f_a->denominator;
	return (left_side < right_side) ? -1 : (left_side > right_side);
}

/**
 * @brief Reduces a given fraction in place.
 *
 * If the fraction is already simplified (*i.e.* its numerator and denominator
 * are relatively primes), it is not simplified further and the function
 * returns false.
 *
 * @param [in,out] fraction The fraction of simplify.
 *
 * @return Whether the fraction was simplified.
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

/**
 * @brief Gives the invert of a fraction.
 *
 * @warning If the input fraction is null (its numerator is 0), no action is
 * performed and the value of *result is not modified.
 *
 * @param[in] input_frac The fraction to invert.
 * @param[out] result Where to store the inverted fraction.
 */
void
invert_fraction(const fraction *const input_frac, fraction *const result)
{
	if (input_frac->numerator == 0) {
		return;
	}
	result->numerator = input_frac->denominator;
	result->denominator = input_frac->numerator;
}
