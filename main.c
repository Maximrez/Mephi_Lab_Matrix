#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

//Ввод с клавиатуры вещественной матрицы
Matrix *input_double() {
    int r, c;
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
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("matrix[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", (double *) ((*m).values[i][j]));
        }
    }
    return m;
}

//Ввод с клавиатуры комплексной матрицы
Matrix *input_complex() {
    int r, c;
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
    printf("Enter two numbers separated by a space!");
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double a, b;
            printf("matrix[%d][%d]: ", i + 1, j + 1);
            scanf("%lf%lf", &a, &b);
            *(double complex *) ((*m).values[i][j]) = a + b * I;
        }
    }
    return m;
}

//Выбор режима создания вещественной матрицы
Matrix *choose_create_double() {
    printf("Select the way to create matrix:\n1 - input from keyboard\n2 - create identity\n3 - create random\n");
    int s = 0, r, c;
    while ((s < 1) || (s > 3)) {
        scanf("%d", &s);
        switch (s) {
            case 1: {
                Matrix *m = input_double();
                return m;
            }
            case 2: {
                printf("side: ");
                scanf("%d", &r);
                while (r < 1) {
                    printf("Enter a positive integer!\nside: ");
                    scanf("%d", &r);
                }
                Matrix *m = creat_identity_double(r);
                return m;
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
                Matrix *m = creat_random_double(r, c);
                return m;
            }
            default: {
                printf("Enter a number from the list!\n");
                break;
            }
        }
    }
    return NULL;
}

//Выбор режима создания комплексной матрицы
Matrix *choose_create_complex() {
    printf("Select the way to create matrix:\n1 - input from keyboard\n2 - create identity\n3 - create random\n");
    int s = 0, r, c;
    while ((s < 1) || (s > 3)) {
        scanf("%d", &s);
        switch (s) {
            case 1: {
                Matrix *m = input_complex();
                return m;
            }
            case 2: {
                printf("side: ");
                scanf("%d", &r);
                while (r < 1) {
                    printf("Enter a positive integer!\nside: ");
                    scanf("%d", &r);
                }
                Matrix *m = creat_identity_complex(r);
                return m;
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
                Matrix *m = creat_random_complex(r, c);
                return m;
            }
            default: {
                printf("Enter a number from the list!\n");
                break;
            }
        }
    }
    return NULL;
}

//Вывод на экран вещественную матрицу
void print_double(Matrix *m) {
    for (int i = 0; i < (*m).rows; i++) {
        printf("|");
        for (int j = 0; j < (*m).columns; j++) {
            printf("%.1lf", *(double *) ((*m).values[i][j]));
            if (j < (*m).columns - 1)
                printf("   ");
        }
        printf("|\n");
    }
    printf("\n");
}

//Вывод на экран комплексную матрицу
void print_complex(Matrix *m) {
    for (int i = 0; i < (*m).rows; i++) {
        printf("|");
        for (int j = 0; j < (*m).columns; j++) {
            double complex v = *(double complex *) (*m).values[i][j];
            if (cimag(v) < 0) {
                printf("%.1f - %.1f*I", creal(v), fabs(cimag(v)));
            } else {
                printf("%.1f + %.1f*I", creal(v), cimag(v));
            }
            if (j < (*m).columns - 1)
                printf("   ");
        }
        printf("|\n");
    }
    printf("\n");
}

//Цикл действий с вещественными матрицами
void action_cycle_double(Matrix *m) {
    int s = 0, i, j;
    while (s != 8) {
        printf("\nYour matrix:\n");
        print_double(m);
        printf("Select the action with matrix:\n1 - input new matrix\n2 - change element\n3 - multiply by scalar\n4 - transpose\n5 - add matrix\n6 - subtract matrix\n7 - multiply by matrix\n8 - exit\n");
        scanf("%d", &s);
        switch (s) {
            case 1: {
                m = choose_create_double();
                break;
            }
            case 2: {
                printf("row (from 1 to %d): ", (*m).rows);
                scanf("%d", &i);
                while ((i < 1) || (i > (*m).rows)) {
                    printf("Index out of rows!\nrow (from 1 to %d): ", (*m).rows);
                    scanf("%d", &i);
                }
                printf("columns (from 1 to %d): ", (*m).columns);
                scanf("%d", &j);
                while ((j < 1) || (j > (*m).columns)) {
                    printf("Index out of rows!\nrow (from 1 to %d): ", (*m).columns);
                    scanf("%d", &j);
                }
                printf("old value: %.1lf\nnew value: ", *(double *) (*m).values[i - 1][j - 1]);
                scanf("%lf", (double *) ((*m).values[i - 1][j - 1]));
                break;
            }
            case 3: {
                printf("scalar: ");
                double k;
                scanf("%lf", &k);
                m = mul_scalar_matrix_double(m, k);
                break;
            }
            case 4: {
                m = transpose_matrix(m);
                break;
            }
            case 5: {
                Matrix *m1 = choose_create_double();
                printf("\nNew matrix:\n");
                print_double(m1);
                m = add_matrix_double(m, m1);
                break;
            }
            case 6: {
                Matrix *m1 = choose_create_double();
                printf("\nNew matrix:\n");
                print_double(m1);
                m = subtract_matrix_double(m, m1);
                break;
            }
            case 7: {
                Matrix *m1 = choose_create_double();
                printf("\nNew matrix:\n");
                print_double(m1);
                m = mul_matrix_double(m, m1);
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
}

//Цикл действий с комплексными матрицами
void action_cycle_complex(Matrix *m) {
    int s = 0, i, j;
    while (s != 8) {
        printf("\nYour matrix:\n");
        print_complex(m);
        printf("Select the action with matrix:\n1 - input new matrix\n2 - change element\n3 - multiply by scalar\n4 - transpose\n5 - add matrix\n6 - subtract matrix\n7 - multiply by matrix\n8 - exit\n");
        scanf("%d", &s);
        switch (s) {
            case 1: {
                m = choose_create_complex();
                break;
            }
            case 2: {
                printf("row (from 1 to %d): ", (*m).rows);
                scanf("%d", &i);
                while ((i < 1) || (i > (*m).rows)) {
                    printf("Index out of rows!\nrow (from 1 to %d): ", (*m).rows);
                    scanf("%d", &i);
                }
                printf("columns (from 1 to %d): ", (*m).columns);
                scanf("%d", &j);
                while ((j < 1) || (j > (*m).columns)) {
                    printf("Index out of rows!\nrow (from 1 to %d): ", (*m).columns);
                    scanf("%d", &j);
                }
                double complex v = *(double complex *) (*m).values[i - 1][j - 1];
                if (cimag(v) < 0) {
                    printf("old value: %.1f - %.1f*I\nnew value (two numbers separated by a space): ", creal(v),
                           fabs(cimag(v)));
                } else {
                    printf("old value: %.1f + %.1f*I\nnew value (two numbers separated by a space): ", creal(v),
                           cimag(v));
                }
                double a, b;
                scanf("%lf%lf", &a, &b);
                *(double complex *) ((*m).values[i - 1][j - 1]) = a + b * I;
                break;
            }
            case 3: {
                printf("complex scalar (two numbers separated by a space): ");
                double a, b;
                scanf("%lf%lf", &a, &b);
                m = mul_scalar_matrix_complex(m, a + b * I);
                break;
            }
            case 4: {
                m = transpose_matrix(m);
                break;
            }
            case 5: {
                Matrix *m1 = choose_create_complex();
                printf("\nNew matrix:\n");
                print_complex(m1);
                m = add_matrix_complex(m, m1);
                break;
            }
            case 6: {
                Matrix *m1 = choose_create_complex();
                printf("\nNew matrix:\n");
                print_complex(m1);
                m = subtract_matrix_complex(m, m1);
                break;
            }
            case 7: {
                Matrix *m1 = choose_create_complex();
                printf("\nNew matrix:\n");
                print_complex(m1);
                m = mul_matrix_complex(m, m1);
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
}

int main() {
    printf("Select the type of matrices:\n1 - double\n2 - complex\n");
    int s = 0;
    while ((s < 1) || (s > 2)) {
        scanf("%d", &s);
        switch (s) {
            case 1: {
                Matrix *m = choose_create_double();
                action_cycle_double(m);
                break;
            }
            case 2: {
                Matrix *m = choose_create_complex();
                action_cycle_complex(m);
                break;
            }
            default: {
                printf("Enter a number from the list!\n");
                break;
            }
        }
    }
}