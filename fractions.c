/**
 * @file fractions.c
 * @brief Implementation of mathematical operations for fractions.
 *
 * Most functions operate on @ref fraction structures.
 *
 * @see fractions.h
 */
#include "fractions.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>

/* -- Helper functions -- */

/**
 * @brief Gives the GCD of two _positive_ integers.
 *
 * Computes the greatest commom divisor (GCD) of the two integers using the
 * Euclidian algorithm.
 *
 * @param[in] a One of the integers to compute the GCD of.
 * @param[in] b One of the integers to compute the GCD of.
 *
 * @return The GCD of its inputs.
 */
unsigned int
gcd(unsigned int a, unsigned int b)
{
	while (b != 0) {
		unsigned int t = b;
		b = a % b;
		a = t;
	}
	return a;
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
	result->negative = fraction_in1->negative != fraction_in2->negative;
	result->numerator = fraction_in1->numerator * fraction_in2->numerator;
	result->denominator =
	    fraction_in1->denominator * fraction_in2->denominator;
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
/*
 * Using longs and downcasting seemed a quite good option to me, no overflow to
 * care about.
 */
void
substract_fractions(const fraction *const fraction1,
                    const fraction *const fraction2, fraction *const result)
{
	long int wide_num1 =
	    (long int)fraction1->numerator * (fraction1->negative ? -1 : 1);
	long int wide_num2 =
	    (long int)fraction2->numerator * (fraction2->negative ? -1 : 1);
	long int wide_result = 0;
	if (fraction1->denominator == fraction2->denominator) {
		wide_result = wide_num1 - wide_num2;
		result->denominator = fraction1->denominator;
	} else {
		wide_result = wide_num1 * fraction2->denominator -
		              wide_num2 * fraction1->denominator;
		result->denominator =
		    fraction1->denominator * fraction2->denominator;
	}
	result->negative = (wide_result < 0);
	/* This should always be true, but the compiler needs convincing */
	assert(wide_result < (long)UINT_MAX ||
	       wide_result > (long)UINT_MAX * -1);
	result->numerator =
	    (unsigned int)(wide_result < 0 ? -wide_result : wide_result);
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
	if (f_a->negative == 0 && f_b->negative == 0) {
		return (left_side < right_side) ? -1 : (left_side > right_side);
	} else if (f_a->negative == 1 && f_b->negative == 1) {
		return (left_side > right_side) ? -1 : (left_side < right_side);
	} else if (f_a->negative == 0 && f_b->negative == 1) {
		return 1;
	} else {
		return -1;
	}
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
	/* If the fraction is equal to zero, we chose to force the
	 * denominator to 1, make it positive and consider it reduced */
	if (fraction->numerator == 0) {
		fraction->negative = 0;
		fraction->denominator = 1;
		return true;
	}
	unsigned int divisor = gcd(fraction->numerator, fraction->denominator);
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
	result->negative = input_frac->negative;
	result->numerator = input_frac->denominator;
	result->denominator = input_frac->numerator;
}

/**
 * @brief Gives the sign of a fraction as a printable character.
 *
 * The character is '+' if the fraction is positive, and '-' if it is negative.
 *
 * @param[in] fraction The fraction to describe.
 *
 * @return A character representing the sign of the fraction.
 */
char
fraction_sign_as_character(const fraction *const fraction)
{
	return fraction->negative ? '-' : '+';
}

void
fraction_from_int(int input, fraction *const output)
{
	output->denominator = 1;
	if (input < 0) {
		output->negative = true;
		output->numerator = -input;
	} else {
		output->negative = false;
		output->numerator = input;
	}
}
