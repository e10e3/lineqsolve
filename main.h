#include <stdio.h>
#include <stdlib.h>

#define FILENAME_IN "matrix.txt"

extern int count_char_in_string(const char, const char*);
extern void pp_matrix(int** const, const int, const int);
extern void gauss_pivot(int** const, const int, const int);
