#include <matrix.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

bool _valid_matrix_verbose_light(struct matrix *m)
{
    if (!m)
    {
        printf("Matrix is NULL\n");
        return false;
    }
    if (!m->data)
    {
        printf("Matrix data is NULL\n");
        return false;
    }
    return true;
}

struct matrix *matrix_factory(size_t rows, size_t cols)
{
    struct matrix *ret = malloc(sizeof(struct matrix));
    if (ret == NULL)
    {
        printf("Matrix malloc failed\n");
        goto FAILED;
    }

    ret->data = malloc(sizeof(float *) * rows);
    if (ret == NULL)
    {
        printf("Data malloc failed\n");
        goto FAILED;
    }

    for (int i = 0; i < rows; ++i)
    {
        ret->data[i] = malloc(sizeof(float) * cols);
        if (ret == NULL)
        {
            printf("Data col malloc failed\n");
            goto FAILED;
        }
    }

    ret->rows = rows;
    ret->cols = cols;
    return ret;

FAILED:
    free_matrix(ret);
    printf("matrix_factory failed\n");
    return NULL;
}

void free_matrix(struct matrix *m)
{
    if (m)
    {
        if (m->data)
        {
            for (int i = 0; i < m->rows; ++i)
            {
                if (m->data[i])
                {
                    free(m->data[i]);
                }
            }
            free(m->data);
        }
        free(m);
    }
}

void insert(struct matrix *m, size_t row, size_t col, float val)
{
    if (!_valid_matrix_verbose_light(m))
    {
        printf("insert failed\n");
        return;
    }
    m->data[row][col] = val;
}

void insert_row(struct matrix *m, size_t rowi, const float *row, size_t lrow)
{
    if (!_valid_matrix_verbose_light(m))
    {
        printf("insert_row failed\n");
        return;
    }
    if (lrow != m->cols)
    {
        printf("insert_row failed - lrow %d if greater than row capacity: %d\n", lrow, m->cols);
        return;
    }
    if (rowi >= m->rows)
    {
        printf("insert_row failed - rowi: %d is greater than num rows of matrix: %d\n", rowi, m->rows);
        return;
    }
    memcpy(m->data[rowi], row, lrow * sizeof(float));
}

void _unsafe_pretty_print_row_carriage_return(struct matrix *m, size_t rowi)
{
    for (int i = 0; i < m->cols; ++i)
    {
        printf("%10.3f ", m->data[rowi][i]);
    }
    printf("\n");
}

void pretty_print(struct matrix *m)
{
    if (!_valid_matrix_verbose_light(m))
    {
        printf("pretty_print failed\n");
        return;
    }
    for (int i = 0; i < m->rows; ++i)
    {
        _unsafe_pretty_print_row_carriage_return(m, i);
    }
}
