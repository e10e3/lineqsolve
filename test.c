#include "fractions.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_substraction(void);
void test_simplification(void);
void test_multiplication(void);
void test_comparison(void);

int
main(void)
{
	test_comparison();
	test_substraction();
	test_simplification();
	test_multiplication();
	printf("All good.\n");
	return EXIT_SUCCESS;
}

void
test_substraction(void)
{
	{
		/* Standard substraction */
		fraction frac1 = {0, 8, 3};
		fraction frac2 = {0, 4, 2};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 2, 3};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Substracting zero */
		fraction frac1 = {0, 2, 7};
		fraction frac2 = {0, 0, 5};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 2, 7};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Substracting whole numbers */
		fraction frac1 = {0, 18, 1};
		fraction frac2 = {0, 5, 1};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 13, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Substracting a negative number */
		fraction frac1 = {0, 3, 1};
		fraction frac2 = {1, 2, 1};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {0, 5, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Substracting a bigger number */
		fraction frac1 = {0, 5, 1};
		fraction frac2 = {0, 7, 1};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {1, 2, 1};
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
}

void
test_comparison(void) {
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
