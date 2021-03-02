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
    (*m).values = (void ***) malloc(sizeof(void **) * r);
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
void *mul_matrix_double(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if ((*m_a).columns != (*m_a).rows) {
        printf("It is not possible to multiply matrices!\n");
        return m_a;
    }
    int r = (*m_a).rows, c = (*m_a).columns, n = (*m_a).columns;
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double *) (*m).values[i][j] = (double) 0;
            for (int k = 0; k < n; k++) {
                *(double *) (*m).values[i][j] += *(double *) (*m_a).values[i][k] * *(double *) (*m_b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Перемножает комплексные матрицы
void *mul_matrix_complex(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if ((*m_a).columns != (*m_b).rows) {
        printf("It is not possible to multiply matrices!\n");
        return m_a;
    }
    int r = (*m_a).rows, c = (*m_b).columns, n = (*m_a).columns;
    Matrix *m = create_matrix(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double *) (*m).values[i][j] = (double complex) 0;
            for (int k = 0; k < n; k++) {
                *(double complex *) (*m).values[i][j] +=
                        *(double complex *) (*m_a).values[i][k] * *(double complex *) (*m_b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Умножает вещественную матрицу на вещественный скаляр
void *mul_scalar_matrix_double(void *a, double scalar) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            *(double *) (*m_a).values[i][j] = scalar * *(double *) (*m_a).values[i][j];
        }
    }
    return m_a;
}

//Умножает комплексную матрицу на комплексный скаляр
void *mul_scalar_matrix_complex(void *a, double scalar) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            *(double complex *) (*m_a).values[i][j] = scalar * *(double complex *) (*m_a).values[i][j];
        }
    }
    return m_a;
}

//Добавляет вещественную матрицу
void *add_matrix_double(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if (((*m_a).rows != (*m_b).rows) || ((*m_a).columns != (*m_b).columns)) {
        printf("It is impossible to add matrix!\n");
        return m_a;
    }
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            *(double *) (*m_a).values[i][j] += *(double *) (*m_b).values[i][j];
        }
    }
    printf("Operation completed successfully!\n");
    return m_a;
}

//Добавляет комплексную матрицу
void *add_matrix_complex(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if (((*m_a).rows != (*m_b).rows) || ((*m_a).columns != (*m_b).columns)) {
        printf("It is impossible to add matrix!\n");
        return m_a;
    }
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            *(double complex *) (*m_a).values[i][j] += *(double complex *) (*m_b).values[i][j];
        }
    }
    printf("Operation completed successfully!\n");
    return m_a;
}

//Вычитает вещественную матрицу
void *subtract_matrix_double(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if (((*m_a).rows != (*m_b).rows) || ((*m_a).columns != (*m_b).columns)) {
        printf("It is impossible to subtract matrix!\n");
        return m_a;
    }
    return add_matrix_double(m_a, mul_scalar_matrix_double(m_b, (double) -1));
}

//Вычитает комплексную матрицу
void *subtract_matrix_complex(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if (((*m_a).rows != (*m_b).rows) || ((*m_a).columns != (*m_b).columns)) {
        printf("It is impossible to subtract matrix!\n");
        return m_a;
    }
    return add_matrix_complex(m_a, mul_scalar_matrix_complex(m_b, (double complex) -1));
}

//Транспонирует матрицу
void *transpose_matrix(void *a) {
    Matrix *m_a = (Matrix *) a;
    Matrix *t = create_matrix((*m_a).columns, (*m_a).rows);
    for (int i = 0; i < (*t).rows; i++) {
        for (int j = 0; j < (*t).columns; j++) {
            (*t).values[i][j] = (*m_a).values[j][i];
        }
    }
    return t;
}