/**
 * @file main.c
 * @brief The main logic file.
 *
 * The matrix used in this program is modeled as a 2D array of fractions, with
 * \f$n_{\mathrm{lines}}\times n_{\mathrm{col}}\f$ elements.
 *
 * The matrix is referenced in a line-column fashion (row-major). *I.e.* the
 * value at `matrix[0][1]` is the element at the intersection of the first line
 * and the second colum.
 */

#include "main.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief The file to read for the input matrix in case none is given as an
 * argument.
 */
#define DEFAULT_FILENAME_IN "matrix.txt"

/**
 * @brief Counts the occurences of a character in a string.
 *
 * @param[in] to_search The character to look for.
 * @param[in] string The string to search in.
 *
 * @return The number of matches.
 */
int
count_char_in_string(const char to_search, const char *string)
{
	int count = 0;
	while (*string != '\0') {
		if (*string == to_search) {
			count++;
		}
		string++;
	}
	return count;
}

/**
 * @brief Pretty-prints a matrix.
 *
 * Prints a 2D array of fractions on the standard output, formatted as a
 * matrix.
 *
 * @param[in] matrix The matrix to print.
 * @param[in] n_lines The number of lines of the matrix.
 * @param[in] n_col The number of columns of the matrix.
 */
void
pp_matrix(fraction **const matrix, const int n_lines, const int n_col)
{
	/*
	 * The matrix is pretty-printed with brackets represented either
	 * with parenthesises for single-line matrix or with a combination of
	 * slashes and vertical bars for multi-line matrixes.
	 */
	printf("\n");
	for (int i = 0; i < n_lines; i++) {
		if (i == 0) {
			if (n_lines == 1) {
				printf("(");
			} else {
				printf("⎛");
			}
		} else if (i == n_lines - 1) {
			printf("⎝");
		} else {
			printf("⎜");
		}

		for (int j = 0; j < n_col; j++) {
			printf("%d/%d", matrix[i][j].numerator,
			       matrix[i][j].denominator);
			if (j != n_col - 1) {
				printf(" ");
			}
		}

		if (i == 0) {
			if (n_lines == 1) {
				printf(")");
			} else {
				printf("⎞");
			}
		} else if (i == n_lines - 1) {
			printf("⎠");
		} else {
			printf("⎟");
		}
		printf("\n");
	}
}

/**
 * @brief Finds the greatest fraction in matrix's column.
 *
 * @param[in] matrix The matrix to search the values in.
 * @param[in] column The index of the column to search in.
 * @param[in] n_lines The number of lines in the matrix.
 *
 * @return The line number of the column's greatest item.
 */
int
find_greatest_value_in_column(fraction **const matrix, const int column,
                              const int n_lines)
{
	/* Start with the smallest possible value */
	fraction current_max_val = {INT_MIN, 1};
	int current_max_index = 0;
	for (int i = 0; i < n_lines; i++) {
		if (compare_fractions(&matrix[i][column], &current_max_val) ==
		    0) {
			current_max_val = matrix[i][column];
			current_max_index = i;
		}
	}
	return current_max_index;
}

/**
 * @brief Substract two matrix lines in places
 *
 * Piece-wise removes the value in line2 from line1, and stores the result in
 * line1.
 *
 * @param[in, out] line1 Pointer to the first item of the line being substracted
 * from.
 * @param[in] line2 Pointer to the line being substracted.
 * @param[in] n_col The number of columns in the matrix.
 */
void
substract_lines_in_place(fraction *const line1, fraction *const line2,
                         const int n_col)
{
	for (int i = 0; i < n_col; i++) {
		substract_fractions(line1 + i, line2 + i, &line1[i]);
	}
}

/**
 * @brief Multiplies the values in the line by a fraction.
 *
 * The fractions in the line are multiplied in place by the indicated fraction.
 *
 * @param[in, out] line Pointer to the first item of the line being multiplied.
 * @param[in] factor The fraction to multiply the line by.
 * @param[in] n_col The number of columns in the line.
 */
void
multiply_line_in_place(fraction *const line, const fraction factor,
                       const int n_col)
{
	for (int i = 0; i < n_col; i++) {
		multiply_fractions(line + i, &factor, &line[i]);
	}
}

/**
 * @brief Computes a row-echelon form of the matrix.
 *
 * Uses Gauss' method (row operations) to find a row-echelon form of the matrix.
 * The matrix is modified in place.
 *
 * @param[in, out] matrix The matrix to manipulate.
 * @param[in] n_lines The number of lines in the matrix.
 * @param[in] n_col The number of columns in the matrix.
 */
void
triangularise(fraction **const matrix, const int n_lines, const int n_col)
{
	/* For each step, the pivot is in position (i, i) */
	for (int i = 0; i < n_lines; i++) {
		/* Make the line with the biggest value of the
		 * column the pivot line */
		int line_pivot =
		    find_greatest_value_in_column(matrix, i, n_lines);
		if (line_pivot > i) {
			/* Make the greatest value the pivot, for greater
			 * stability */
			fraction *temp_line = matrix[i];
			matrix[i] = matrix[line_pivot];
			matrix[line_pivot] = temp_line;
		}

		fraction inverse_of_pivot = {0};
		invert_fraction(&matrix[i][i], &inverse_of_pivot);

		fraction *substracted_line =
		    (fraction *)malloc(n_col * sizeof(fraction));
		for (int j = 0; j < n_lines; j++) {
			if (j == i) {
				/* This is the pivot */
				continue;
			}
			/* Determine the factor */
			fraction simplification_factor = {0};
			multiply_fractions(&matrix[j][i], &inverse_of_pivot,
			                   &simplification_factor);
			/* Pre-multiply (a copy of!) the pivot's line */
			substracted_line = memcpy(substracted_line, matrix[i],
			                          n_col * sizeof(fraction));
			multiply_line_in_place(substracted_line,
			                       simplification_factor, n_col);
			/* Substract the lines */
			substract_lines_in_place(matrix[j], substracted_line,
			                         n_col);
		}
		free(substracted_line);
	}
}

/**
 * @brief Reduces a matrix in upper-echelon form.
 *
 * Uses back-substitution to transform a matrix in row-echelon form to its
 * reduced-row-echelon form.
 *
 * This function is currently unsued.
 *
 * @param[in,out] matrix The matrix to reduce.
 * @param[in] n_lines The number of lines in the matrix.
 * @param[in] n_col The number of columns in the matrix.
 */
void
diagonalise(fraction **const matrix, const int n_lines, const int n_col)
{
}

/**
 * @brief Performs the gaussian elimination method on the matrix.
 *
 * Uses the gaussian elimitation method on an augmented matrix to find the
 * solution of its corresponding system of linear equations. The matrix is
 * modified in place.
 *
 * @param[in, out] matrix The matrix system to resolve.
 * @param[in] n_lines The number of lines in the matrix.
 * @param[in] n_col The number of columns in the matrix.
 */
void
gaussian_elimination(fraction **const matrix, const int n_lines,
                     const int n_col)
{
	triangularise(matrix, n_lines, n_col);
	diagonalise(matrix, n_lines, n_col);
}

/**
 * @brief Prints the solution to the linear equation system after gaussian
 * elimination.
 *
 * @param[in] matrix The matrix to print.
 * @param[in] n_lines The number of lines in the matrix.
 * @param[in] n_col The number of columns in the matrix.
 */
void
print_results(fraction **const matrix, const int n_lines, const int n_col)
{
	for (int i = 0; i < n_lines; i++) {
		fraction inverted_pivot = {0};
		invert_fraction(&matrix[i][i], &inverted_pivot);
		fraction var_i_val = {0};
		multiply_fractions(&matrix[i][n_col - 1], &inverted_pivot,
		                   &var_i_val);
		float var_i_approx =
		    var_i_val.numerator * 1.0 / var_i_val.denominator;
		printf("The value of the variable %d is: %g (%d/%d).\n", i + 1,
		       var_i_approx, var_i_val.numerator,
		       var_i_val.denominator);
	}
}

/**
 * @brief The entry point of the program.
 *
 * Handles reading the input files and creating the matrix.
 *
 * @param[in] argc The number of arguments supplied to the program.
 * @param[in] argv The array containing the arguments.
 *
 * @return The ending status of the program.
 */
int
main(const int argc, char *const argv[])
{
	int number_variables = 0;
	fraction **values_matrix = {0};
	char *input_filename = "";

	if (argc == 0) {
		fprintf(stderr,
		        "ERROR: number of arguments should not be 0.\n");
		exit(EXIT_FAILURE);
	} else if (argc == 1) {
		input_filename = DEFAULT_FILENAME_IN;
	} else if (argc == 2) {
		input_filename = argv[1];
	} else {
		fprintf(stderr, "ERROR: only 1 or 2 arguments expected.\n");
		exit(EXIT_FAILURE);
	}

	FILE *input = fopen(input_filename, "r");
	if (input == NULL) {
		fprintf(stderr, "ERROR: could not open file %s.\n",
		        input_filename);
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Reading the file\n");

	char string[256];
	/* Read until a newline is reached */
	fscanf(input, "%[^\n]", string);
	rewind(input);

	number_variables = count_char_in_string(' ', string);
	fprintf(stderr, "This system has %d variables.\n", number_variables);

	/* n variables + result */
	values_matrix =
	    (fraction **)malloc(number_variables * sizeof(fraction *));
	for (int i = 0; i < number_variables; i++) {
		values_matrix[i] = (fraction *)malloc((number_variables + 1) *
		                                      sizeof(fraction));
	}

	for (int i = 0; i < (number_variables); i++) {
		for (int j = 0; j < (number_variables + 1); j++) {
			fscanf(input, "%d", &values_matrix[i][j].numerator);
			values_matrix[i][j].denominator = 1;
		}
	}

	fclose(input);
	fprintf(stderr, "File closed\n");

	printf("Initial matrix:");
	pp_matrix(values_matrix, number_variables, number_variables + 1);
	gaussian_elimination(values_matrix, number_variables,
	                     number_variables + 1);
	printf("\nFinal matrix:");
	pp_matrix(values_matrix, number_variables, number_variables + 1);

	print_results(values_matrix, number_variables, number_variables + 1);

	for (int i = 0; i < number_variables; i++) {
		free(values_matrix[i]);
	}
	free(values_matrix);

	return EXIT_SUCCESS;
}
