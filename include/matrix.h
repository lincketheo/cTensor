#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stddef.h>

struct matrix
{
    float **data;
    size_t rows;
    size_t cols;
};

struct matrix *matrix_factory(size_t rows, size_t cols);
void free_matrix(struct matrix *m);
void insert(struct matrix *m, size_t row, size_t col, float val);
void insert_row(struct matrix *m, size_t rowi, const float *row, size_t lrow);
void pretty_print(struct matrix *m);

#endif