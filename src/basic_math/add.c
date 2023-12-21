#include <basic_math/add.h>
#include <stdbool.h>
#include <stdio.h>

bool add_compatability(const struct matrix *left, const struct matrix *right)
{
    return left->cols == right->cols && left->rows == right->rows;
}

struct matrix *add(const struct matrix *left, const struct matrix *right)
{
    struct matrix *ret = matrix_factory(left->rows, left->cols);
    if (!add_compatability(left, right))
    {
        printf("Can't add matrices together of differing dimensions\n");
        goto FAILURE;
    }

    for (int i = 0; i < left->rows; ++i)
    {
        int count = left->cols;
        int n = (count + 7) / 8;
        printf("here %d %d %d\n", i, count, n);
        printf("%f\n", left->data[i][0]);
        switch (count % 8)
        {
        case 0: do { ret->data[i][7 + n*8] = left->data[i][7 + n*8] + right->data[i][7 + n*8];
        case 7:      ret->data[i][6 + n*8] = left->data[i][6 + n*8] + right->data[i][6 + n*8];
        case 6:      ret->data[i][5 + n*8] = left->data[i][5 + n*8] + right->data[i][5 + n*8];
        case 5:      ret->data[i][4 + n*8] = left->data[i][4 + n*8] + right->data[i][4 + n*8];
        case 4:      ret->data[i][3 + n*8] = left->data[i][3 + n*8] + right->data[i][3 + n*8];
        case 3:      ret->data[i][2 + n*8] = left->data[i][2 + n*8] + right->data[i][2 + n*8];
        case 2:      ret->data[i][1 + n*8] = left->data[i][1 + n*8] + right->data[i][1 + n*8];
        case 1:      ret->data[i][0 + n*8] = left->data[i][0 + n*8] + right->data[i][0 + n*8];
            } while (--n > 0);
        }
    }

    return ret;

FAILURE:
    free_matrix(ret);
}
void _add(const struct matrix *left, struct matrix *into)
{
}