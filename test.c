#include "fractions.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_subtraction(void);
void test_simplification(void);
void test_multiplication(void);
void test_comparison(void);
void test_conversion(void);

int
main(void)
{
	test_comparison();
	test_subtraction();
	test_simplification();
	test_multiplication();
	test_conversion();
	printf("All good.\n");
	return EXIT_SUCCESS;
}

void
test_subtraction(void)
{
	{
		/* Standard subtraction */
		fraction frac1 = {0, 8, 3};
		fraction frac2 = {0, 4, 2};
		fraction result = {0};
		subtract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 2, 3};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Subtracting zero */
		fraction frac1 = {0, 2, 7};
		fraction frac2 = {0, 0, 5};
		fraction result = {0};
		subtract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 2, 7};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Subtracting whole numbers */
		fraction frac1 = {0, 18, 1};
		fraction frac2 = {0, 5, 1};
		fraction result = {0};
		subtract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 13, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Subtracting a negative number */
		fraction frac1 = {0, 3, 1};
		fraction frac2 = {1, 2, 1};
		fraction result = {0};
		subtract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 5, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Subtracting a bigger number */
		fraction frac1 = {0, 5, 1};
		fraction frac2 = {0, 7, 1};
		fraction result = {0};
		subtract_fractions(&frac1, &frac2, &result);
		fraction theorical = {1, 2, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Subtracting a small number to a big one */
		fraction frac1 = {0, 65536, 2};
		fraction frac2 = {0, 1, 65538};
		fraction result = {0};
		subtract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 2147549183, 65538};
		assert(compare_fractions(&result, &theorical) == 0);
	}
}

void
test_simplification(void)
{
	{
		/* Multiples */
		fraction frac1 = {0, 4, 2};
		simplify_fraction(&frac1);
		fraction theorical = {0, 2, 1};
		assert(compare_fractions(&frac1, &theorical) == 0);
	}
	{
		/* Unit fraction */
		fraction frac1 = {1, 5, 5};
		simplify_fraction(&frac1);
		fraction theorical = {1, 1, 1};
		assert(compare_fractions(&frac1, &theorical) == 0);
	}
}

void
test_multiplication(void)
{
	{
		/* Regular, same denominator, no simplification */
		fraction frac1 = {0, 3, 5};
		fraction frac2 = {0, 2, 5};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 6, 25};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Division */
		/* Multiplying by 1/2 is the same as dividing by 2. */
		fraction frac1 = {0, 1, 2};
		fraction frac2 = {0, 4, 1};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 2, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* One negative */
		fraction frac1 = {1, 8, 7};
		fraction frac2 = {0, 3, 10};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {1, 12, 35};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Two negatives */
		fraction frac1 = {1, 2, 3};
		fraction frac2 = {1, 7, 5};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 14, 15};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Whole numbers */
		fraction frac1 = {0, 5, 1};
		fraction frac2 = {0, 4, 1};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 20, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Identity */
		fraction frac1 = {0, 29, 53};
		fraction frac2 = {0, 1, 1};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 29, 53};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Opposite */
		fraction frac1 = {0, 131, 97};
		fraction frac2 = {1, 1, 1};
		fraction result = {0};
		multiply_fractions(&frac1, &frac2, &result);
		fraction theorical = {1, 131, 97};
		assert(compare_fractions(&result, &theorical) == 0);
	}
}

void
test_comparison(void)
{
	{
		/* Same fraction */
		fraction frac1 = {0, 2, 1};
		fraction frac2 = {0, 2, 1};
		assert(compare_fractions(&frac1, &frac2) == 0);
	}
	{
		/* Different signs */
		fraction frac1 = {0, 5, 7};
		fraction frac2 = {1, 5, 7};
		assert(compare_fractions(&frac1, &frac2) == 1);
	}
	{
		/* Smaller */
		fraction frac1 = {0, 3, 8};
		fraction frac2 = {0, 15, 11};
		assert(compare_fractions(&frac1, &frac2) == -1);
	}
	{
		fraction frac1 = {1, 6, 4};
		fraction frac2 = {0, 9, 7};
		assert(compare_fractions(&frac1, &frac2) == -1);
	}
}

void
test_conversion(void)
{
	{
		/* Zero */
		int32_t number = 0;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {0, 0, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Small integer */
		int32_t number = 1;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {0, 1, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Other integer */
		int32_t number = 59;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {0, 59, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Negative integer */
		int32_t number = -1;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {1, 1, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Other negative integer */
		int32_t number = -99;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {1, 99, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Largest integer */
		int32_t number = 2147483647;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {0, 2147483647, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Largest negative integer */
		int32_t number = -2147483648;
		fraction result = {0};
		fraction_from_int(number, &result);
		fraction theorical = {1, 2147483648, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
}
