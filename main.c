#include "main.h"

#include "fractions.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_FILENAME_IN "matrix.txt"

/*
 * Matrix = 2d array of n_lines elements by n_col fractions
 * The matrix is referenced in line-column fashion
 * i.e. element matrix[0][1] is the element at the intersection
 * of the first line and the second column
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
				printf("/");
			}
		} else if (i == n_lines - 1) {
			printf("\\");
		} else {
			printf("|");
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
				printf("\\");
			}
		} else if (i == n_lines - 1) {
			printf("/");
		} else {
			printf("|");
		}
		printf("\n");
	}
}

/**
 * Returns the line number of the greatest value in the column.
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
 * Subtract line2 from line1 in place
 */
void
substract_lines_in_place(fraction *const line1, fraction *const line2,
                         const int n_col)
{
	for (int i = 0; i < n_col; i++) {
		line1[i] = *substract_fractions(line1 + i, line2 + i);
	}
}

void
multiply_line_in_place(fraction *const line, const fraction factor,
                       const int n_col)
{
	for (int i = 0; i < n_col; i++) {
		line[i] = *multiply_fractions(line + i, &factor);
	}
}

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

		fraction inverse_of_pivot = *invert_fraction(&matrix[i][i]);

		fraction *substracted_line =
		    (fraction *)malloc(n_col * sizeof(fraction));
		for (int j = 0; j < n_lines; j++) {
			if (j == i) {
				/* This is the pivot */
				continue;
			}
			/* Determine the factor */
			fraction simplification_factor = *multiply_fractions(
			    &matrix[j][i], &inverse_of_pivot);
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

void
diagonalise(fraction **const matrix, const int n_lines, const int n_col)
{
}

void
gaussian_elimination(fraction **const matrix, const int n_lines,
                     const int n_col)
{
	triangularise(matrix, n_lines, n_col);
	diagonalise(matrix, n_lines, n_col);
}

void
print_results(fraction **const matrix, const int n_lines, const int n_col)
{
	for (int i = 0; i < n_lines; i++) {
		fraction var_i_val = *multiply_fractions(
		    &matrix[i][n_col - 1], invert_fraction(&matrix[i][i]));
		float var_i_approx =
		    var_i_val.numerator * 1.0 / var_i_val.denominator;
		printf("The value of the variable %d is: %g (%d/%d).\n", i + 1,
		       var_i_approx, var_i_val.numerator,
		       var_i_val.denominator);
	}
}

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
	    (fraction **)malloc(number_variables * sizeof(fraction));
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
