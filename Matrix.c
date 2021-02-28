#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

const int E = 20, P = 0; //Константы рандома (модуль числа и количество цифр после запятой)

//Выделяет память под матрицу и создаёт её
Matrix *create_matrix(int r, int c) {
    Matrix *m = malloc(sizeof(Matrix));
    (*m).rows = *(int *) malloc(sizeof(int));
    (*m).columns = *(int *) malloc(sizeof(int));
    (*m).rows = r;
    (*m).columns = c;
    (*m).values = (void ***) malloc(sizeof(void ***) * r);
    for (int i = 0; i < r; i++) {
        (*m).values[i] = (void **) malloc(sizeof(void **) * c);
        for (int j = 0; j < c; j++) {
            (*m).values[i][j] = (void *) malloc(sizeof(void *));
        }
    }
    return m;
}

//Создаёт единичную вещественную матрицу
Matrix *creat_identity_double(int s) {
    Matrix *m = create_matrix(s, s);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (i == j) {
                *(double *) (*m).values[i][j] = (double) 1;
            } else {
                *(double *) (*m).values[i][j] = (double) 0;
            }
        }
    }
    return m;
}

//Создаёт единичную комплексную матрицу
Matrix *creat_identity_complex(int s) {
    Matrix *m = create_matrix(s, s);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (i == j) {
                *(double complex *) (*m).values[i][j] = (double complex) 1;
            } else {
                *(double complex *) (*m).values[i][j] = (double complex) 0;
            }
        }
    }
    return m;
}

//Создаёт случайно заполненную вещественную матрицу
Matrix *creat_random_double(int r, int c) {
    srand(time(0));
    int d = (int) pow(10, P);
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double *) (*m).values[i][j] = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
        }
    }
    return m;
}

//Создаёт случайно заполненную комплексную матрицу
Matrix *creat_random_complex(int r, int c) {
    srand(time(0));
    int d = (int) pow(10, P);
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double r1 = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
            double r2 = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
            *(double complex *) (*m).values[i][j] = r1 + r2 * I;
        }
    }
    return m;
}

//Перемножает вещественные матрицы
Matrix *mul_matrix_double(Matrix *a, Matrix *b) {
    if ((*a).columns != (*b).rows) {
        printf("It is not possible to multiply matrices!\n");
        return a;
    }
    int r = (*a).rows, c = (*b).columns, n = (*a).columns;
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double *) (*m).values[i][j] = (double) 0;
            for (int k = 0; k < n; k++) {
                *(double *) (*m).values[i][j] += *(double *) (*a).values[i][k] * *(double *) (*b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Перемножает комплексные матрицы
Matrix *mul_matrix_complex(Matrix *a, Matrix *b) {
    if ((*a).columns != (*b).rows) {
        printf("It is not possible to multiply matrices!\n");
        return a;
    }
    int r = (*a).rows, c = (*b).columns, n = (*a).columns;
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double *) (*m).values[i][j] = (double complex) 0;
            for (int k = 0; k < n; k++) {
                *(double complex *) (*m).values[i][j] +=
                        *(double complex *) (*a).values[i][k] * *(double complex *) (*b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Умножает вещественную матрицу на вещественный скаляр
Matrix *mul_scalar_matrix_double(Matrix *a, double scalar) {
    for (int i = 0; i < (*a).rows; i++) {
        for (int j = 0; j < (*a).columns; j++) {
            *(double *) (*a).values[i][j] = scalar * *(double *) (*a).values[i][j];
        }
    }
    return a;
}

//Умножает комплексную матрицу на комплексный скаляр
Matrix *mul_scalar_matrix_complex(Matrix *a, double complex scalar) {
    for (int i = 0; i < (*a).rows; i++) {
        for (int j = 0; j < (*a).columns; j++) {
            *(double complex *) (*a).values[i][j] = scalar * *(double complex *) (*a).values[i][j];
        }
    }
    return a;
}

//Добавляет вещественную матрицу
Matrix *add_matrix_double(Matrix *a, Matrix *b) {
    if (((*a).rows != (*b).rows) || ((*a).columns != (*b).columns)) {
        printf("It is impossible to add matrix!\n");
        return a;
    }
    for (int i = 0; i < (*a).rows; i++) {
        for (int j = 0; j < (*a).columns; j++) {
            *(double *) (*a).values[i][j] += *(double *) (*b).values[i][j];
        }
    }
    printf("Operation completed successfully!\n");
    return a;
}

//Добавляет комплексную матрицу
Matrix *add_matrix_complex(Matrix *a, Matrix *b) {
    if (((*a).rows != (*b).rows) || ((*a).columns != (*b).columns)) {
        printf("It is impossible to add matrix!\n");
        return a;
    }
    for (int i = 0; i < (*a).rows; i++) {
        for (int j = 0; j < (*a).columns; j++) {
            *(double complex *) (*a).values[i][j] += *(double complex *) (*b).values[i][j];
        }
    }
    printf("Operation completed successfully!\n");
    return a;
}

//Вычитает вещественную матрицу
Matrix *subtract_matrix_double(Matrix *a, Matrix *b) {
    if (((*a).rows != (*b).rows) || ((*a).columns != (*b).columns)) {
        printf("It is impossible to subtract matrix!\n");
        return a;
    }
    return add_matrix_double(a, mul_scalar_matrix_double(b, (double) -1));
}

//Вычитает комплексную матрицу
Matrix *subtract_matrix_complex(Matrix *a, Matrix *b) {
    if (((*a).rows != (*b).rows) || ((*a).columns != (*b).columns)) {
        printf("It is impossible to subtract matrix!\n");
        return a;
    }
    return add_matrix_complex(a, mul_scalar_matrix_complex(b, (double complex) -1));
}

//Транспонирует матрицу
Matrix *transpose_matrix(Matrix *a) {
    Matrix *t = create_matrix((*a).columns, (*a).rows);
    for (int i = 0; i < (*t).rows; i++) {
        for (int j = 0; j < (*t).columns; j++) {
            (*t).values[i][j] = (*a).values[j][i];
        }
    }
    return t;
}