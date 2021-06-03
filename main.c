#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "Matrix.h"
#include "tests.h"

// Выбрать как создать матрицу
void *choose_create(int s1) {
    printf("Select the way to create matrix:\n1 - input from keyboard\n2 - create identity\n3 - create random\n");
    int s = 0, r, c;
    while ((s < 1) || (s > 3)) {
        scanf("%d", &s);
        switch (s) {
            case 1: {
                printf("rows: ");
                scanf("%d", &r);
                while (r < 1) {
                    printf("Enter a positive integer!\nrows: ");
                    scanf("%d", &r);
                }
                printf("columns: ");
                scanf("%d", &c);
                while (c < 1) {
                    printf("Enter a positive integer!\ncolumns: ");
                    scanf("%d", &c);
                }
                if (s1 == 1) {
                    Matrix *m = create_matrix(r, c, functions_double);
                    return (*m).input(m);
                }
                if (s1 == 2) {
                    Matrix *m = create_matrix(r, c, functions_complex);
                    return (*m).input(m);
                }
            }
            case 2: {
                printf("side: ");
                scanf("%d", &r);
                while (r < 1) {
                    printf("Enter a positive integer!\nside: ");
                    scanf("%d", &r);
                }
                if (s1 == 1) {
                    return create_identity(r, functions_double);
                }
                if (s1 == 2) {
                    return create_identity(r, functions_complex);
                }
            }
            case 3: {
                printf("rows: ");
                scanf("%d", &r);
                while (r < 1) {
                    printf("Enter a positive integer!\nrows: ");
                    scanf("%d", &r);
                }
                printf("columns: ");
                scanf("%d", &c);
                while (c < 1) {
                    printf("Enter a positive integer!\ncolumns: ");
                    scanf("%d", &c);
                }
                if (s1 == 1) {
                    return create_random_double(r, c);
                }
                if (s1 == 2) {
                    return create_random_complex(r, c);
                }
            }
            default: {
                printf("Enter a number from the list!\n");
                break;
            }
        }
    }
    return NULL;
}

int main() {
    printf("Select the type of matrices or else:\n1 - double\n2 - complex\n3 - run tests\n");
    int s1 = 0;
    Matrix *m;
    while ((s1 < 1) || (s1 > 3)) {
        scanf("%d", &s1);
        switch (s1) {
            case 1: {
                m = choose_create(1);
                break;
            }
            case 2: {
                m = choose_create(2);
                break;
            }
            case 3: {
                test_transpose_double();
                test_transpose_complex();
                test_mul_scalar_matrix_double();
                test_mul_scalar_matrix_complex();
                test_add_matrix_double();
                test_add_matrix_complex();
                test_sub_matrix_double();
                test_sub_matrix_complex();
                test_mul_matrix_double();
                test_mul_matrix_complex();
                printf("All tests passed!");
                exit(0);
            }
            default: {
                printf("Enter a number from the list!\n");
                break;
            }
        }
    }
    int s2 = 0, r, c;
    Matrix *m1;
    while (s2 != 8) {
        printf("\nYour matrix:\n");
        (*m).print(m);
        printf("Select the action with matrix:\n1 - input new matrix\n2 - change element\n3 - multiply by scalar\n4 - transpose\n5 - add matrix\n6 - subtract matrix\n7 - multiply by matrix\n8 - exit\n");
        scanf("%d", &s2);
        switch (s2) {
            case 1: {
                m = choose_create(s1);
                break;
            }
            case 2: {
                printf("row (from 1 to %d): ", (*m).rows);
                scanf("%d", &r);
                while ((r < 1) || (r > (*m).rows)) {
                    printf("Index out of rows!\nrow (from 1 to %d): ", (*m).rows);
                    scanf("%d", &r);
                }
                printf("column (from 1 to %d): ", (*m).columns);
                scanf("%d", &c);
                while ((c < 1) || (c > (*m).columns)) {
                    printf("Index out of columns!\ncolumn (from 1 to %d): ", (*m).columns);
                    scanf("%d", &c);
                }
                printf("old value: ");
                (*m).print_value(m, r - 1, c - 1);
                if (s1 == 1) printf("\nnew value: ");
                if (s1 == 2) printf("\nnew value (two number separated with space): ");
                m = (*m).input_value(m, r - 1, c - 1);
                break;
            }
            case 3: {
                if (s1 == 1) {
                    printf("scalar: ");
                    double k;
                    scanf("%lf", &k);
                    m = (*m).mul_scalar(m, &k);

                }
                if (s1 == 2) {
                    printf("scalar (two numbers separated by a space): ");
                    double k1, k2;
                    scanf("%lf%lf", &k1, &k2);
                    double complex k = k1 + k2 * I;
                    m = (*m).mul_scalar(m, &k);
                }
                break;
            }
            case 4: {
                m = (*m).transpose(m);
                break;
            }
            case 5: {
                m1 = choose_create(s1);
                printf("\nNew matrix:\n");
                (*m1).print(m1);
                m = (*m).add_matrix(m, m1);
                break;
            }
            case 6: {
                m1 = choose_create(s1);
                printf("\nNew matrix:\n");
                (*m1).print(m1);
                m = (*m).sub_matrix(m, m1);
                break;
            }
            case 7: {
                m1 = choose_create(s1);
                printf("\nNew matrix:\n");
                (*m1).print(m1);
                m = (*m).mul_matrix(m, m1);
                break;
            }
            case 8: {
                break;
            }
            default: {
                printf("Enter a number from the list!\n");
                break;
            }
        }
    }
    return 0;
}