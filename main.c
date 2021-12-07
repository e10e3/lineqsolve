#include "main.h"

int number_variables = 0;
int** values_matrix;

int count_char_in_string(const char to_search, const char* string) {
	int count = 0;
	while (*string != '\0') {
		if (*string == to_search) {
			count++;
		}
		string++;
	}
	return count;
}

void pp_matrix(int** const matrix, const int n_lines, const int n_col) {
	/*
	 * Matrix = 2d array of n_lines elements by n_col elements
	 * The matrix is referenced in line-column fashion
	 * i.e. element matrix[0][1] is the element at the intersection
	 * of the first line and the second column
	 */
	printf("\n");
	for (int i = 0; i < n_lines; i++){
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

		for (int j = 0; j < n_col; j++)  {
			printf("%d", matrix[i][j]);
			if (j != n_col - 1){
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

void gauss_pivot(int** const matrix, const int n_lines, const int n_col) {
	pp_matrix(matrix, n_lines, n_col);
}

int main(const int argc, char* const argv[]) {
	FILE* input = fopen(FILENAME_IN, "r");
	printf("Reading the file\n");

	char string[256];
	fscanf(input, "%[^\n]", string);
	rewind(input);

	// printf("The first line is\n > %s\n", string);
	number_variables = count_char_in_string(' ', string);
	printf("This system has %d variables.\n", number_variables);

	/* n variables + result */
	values_matrix = (int**) malloc(number_variables * sizeof(int));
	for (int i = 0; i < number_variables; i++) {
		values_matrix[i] = (int*) malloc((number_variables + 1) * sizeof(int));
	}

	for (int i = 0; i < (number_variables); i++) {
		for (int j = 0; j < (number_variables + 1); j++) {
			fscanf(input, "%d", &values_matrix[i][j]);
		}
	}

	// pp_matrix(values_matrix, number_variables, number_variables + 1);
	// pp_matrix(&values_matrix[1], 1, number_variables + 1);
	gauss_pivot(values_matrix, number_variables, number_variables + 1);

	fclose(input);
	printf("File closed\n");

	for (int i = 0; i < number_variables; i++) {
		free(values_matrix[i]);
	}
	free(values_matrix);
	return EXIT_SUCCESS;
	
}
