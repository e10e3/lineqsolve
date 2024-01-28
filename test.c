#include "fractions.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_substraction();
void test_simplification();
void test_multiplication();

int
main()
{
	test_substraction();
	test_simplification();
	test_multiplication();
	printf("All good.\n");
	return EXIT_SUCCESS;
}

void
test_substraction()
{
	{
		/* Standard substraction */
		fraction frac1 = {8, 3};
		fraction frac2 = {4, 2};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {2, 3};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Substracting zero */
		fraction frac1 = {2, 7};
		fraction frac2 = {0, 5};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {2, 7};
		assert(compare_fractions(&result, &theorical) == 0);
	}
	{
		/* Substracting whole numbers */
		fraction frac1 = {18, 1};
		fraction frac2 = {5, 1};
		fraction result = {0};
		substract_fractions(&frac1, &frac2, &result);
		fraction theorical = {13, 1};
		assert(compare_fractions(&result, &theorical) == 0);
	}
}

void
test_simplification()
{
	fraction frac1 = {4, 2};
	simplify_fraction(&frac1);
	fraction theorical = {2, 1};
	assert(compare_fractions(&frac1, &theorical) == 0);
}

void
test_multiplication()
{
}
