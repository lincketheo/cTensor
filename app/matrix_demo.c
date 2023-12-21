#include <matrix.h>
#include <basic_math/add.h>

int main(int argc, char **argv)
{
    struct matrix *m = matrix_factory(5, 4);
    insert_row(m, 0, (float[]){1, 2, 3, 4}, 4);
    insert_row(m, 1, (float[]){5, 6, 7, 8}, 4);
    insert_row(m, 2, (float[]){9, 10, 11, 12}, 4);
    insert_row(m, 3, (float[]){13, 14, 15, 16}, 4);
    insert_row(m, 4, (float[]){17, 18, 19, 20}, 4);
    printf("\n");
    pretty_print(m);
    struct matrix *m2 = matrix_factory(5, 4);
    insert_row(m2, 0, (float[]){1, 2, 3, 4}, 4);
    insert_row(m2, 1, (float[]){5, 6, 7, 8}, 4);
    insert_row(m2, 2, (float[]){9, 10, 11, 12}, 4);
    insert_row(m2, 3, (float[]){13, 14, 15, 16}, 4);
    insert_row(m2, 4, (float[]){17, 18, 19, 20}, 4);
    pretty_print(m2);
    struct matrix *m3 = add(m, m2);
    printf("\n");
    pretty_print(m3);
    free_matrix(m3);
    free_matrix(m2);
    free_matrix(m);
    return 1;
}
