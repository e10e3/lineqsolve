#include <assert.h>
#include "fractions.h"

void test_addition();
void test_simplification();
void test_multiplication();

int main() {
	test_addition();
	test_simplification();
	test_multiplication();
}

void test_addition() {
	fraction frac1 = {4, 2};
	fraction frac2 = {2, 3};
	fraction* result = add_fractions(&frac1, &frac2);
	fraction theorical = {8, 3};
	assert(are_fractions_equal(result, &theorical));
}

void test_simplification() {
	fraction frac1 = {4, 2};
	simplify_fraction(&frac1);
	fraction theorical = {2, 1};
	assert(are_fractions_equal(&frac1, &theorical));
}

void test_multiplication() {
}

