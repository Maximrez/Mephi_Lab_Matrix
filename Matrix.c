#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

const int E = 20, P = 0; //Константы рандома (модуль числа и количество цифр после запятой)

//Выделяет память под матрицу и создаёт её
void *create_matrix(int r, int c,
                    void *print_value,
                    void *print,
                    void *input_value,
                    void *input,
                    void *transpose,
                    void *mul_scalar,
                    void *mul_matrix,
                    void *add_matrix,
                    void *sub_matrix) {
    Matrix *m = malloc(sizeof(Matrix));
    (*m).rows = *(int *) malloc(sizeof(int));
    (*m).columns = *(int *) malloc(sizeof(int));
    (*m).rows = r;
    (*m).columns = c;
    (*m).values = (void ***) malloc(sizeof(void **) * r);
    for (int i = 0; i < r; i++) {
        (*m).values[i] = (void **) malloc(sizeof(void *) * c);
        for (int j = 0; j < c; j++) {
            (*m).values[i][j] = (void *) malloc(sizeof(void *));
        }
    }
    (*m).print_value = print_value;
    (*m).print = print;
    (*m).input_value = input_value;
    (*m).input = input;
    (*m).transpose = transpose;
    (*m).mul_scalar = mul_scalar;
    (*m).mul_matrix = mul_matrix;
    (*m).add_matrix = add_matrix;
    (*m).sub_matrix = sub_matrix;
    return m;
}

// Создаёт единичную вещественную матрицу
void *create_identity_double(int s) {
    Matrix *m = create_matrix_double(s, s);
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

// Создаёт единичную комплексную матрицу
void *create_identity_complex(int s) {
    Matrix *m = create_matrix_complex(s, s);
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
void *create_random_double(int r, int c) {
    srand(time(0));
    int d = (int) pow(10, P);
    Matrix *m = create_matrix_double(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double *) (*m).values[i][j] = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
        }
    }
    return m;
}

//Создаёт случайно заполненную комплексную матрицу
void *create_random_complex(int r, int c) {
    srand(time(0));
    int d = (int) pow(10, P);
    Matrix *m = create_matrix_complex(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double r1 = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
            double r2 = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
            *(double complex *) (*m).values[i][j] = r1 + r2 * I;
        }
    }
    return m;
}

//Выводит элемент вещественной матрицы
void *print_value_double(void *a, int r, int c) {
    Matrix *m_a = (Matrix *) a;
    printf("%.1lf", *(double *) (*m_a).values[r][c]);
}

//Выводит элемент комплексной матрицы
void *print_value_complex(void *a, int r, int c) {
    Matrix *m_a = (Matrix *) a;
    double complex v = *(double complex *) (*m_a).values[r][c];
    if (cimag(v) < 0) {
        printf("%.1f - %.1f*I", creal(v), fabs(cimag(v)));
    } else {
        printf("%.1f + %.1f*I", creal(v), cimag(v));
    }
    return NULL;
}

//Вывод на экран матрицу
void *print_matrix(void *a) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        printf("|");
        for (int j = 0; j < (*m_a).columns; j++) {
            (*m_a).print_value(m_a, i, j);
            if (j < (*m_a).columns - 1)
                printf("   ");
        }
        printf("|\n");
    }
    printf("\n");
    return NULL;
}

//Ввод с клавиатуры элемента вещественной
void *input_value_double(void *a, int r, int c) {
    Matrix *m_a = (Matrix *) a;
    scanf("%lf", (double *) ((*m_a).values[r][c]));
    return m_a;
}

//Ввод с клавиатуры элемента комплексной матрицы
void *input_value_complex(void *a, int r, int c) {
    Matrix *m_a = (Matrix *) a;
    double d1, d2;
    scanf("%lf%lf", &d1, &d2);
    *(double complex *) ((*m_a).values[r][c]) = d1 + d2 * I;
    return m_a;
}

//Ввод с клавиатуры матрицы
void *input_matrix(void *a) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            printf("matrix[%d][%d]: ", i + 1, j + 1);
            m_a = (*m_a).input_value(m_a, i, j);
        }
    }
    return m_a;
}

//Транспонирует вещественную матрицу
void *transpose_matrix_double(void *a) {
    Matrix *m_a = (Matrix *) a;
    Matrix *t = create_matrix_double((*m_a).columns, (*m_a).rows);
    for (int i = 0; i < (*t).rows; i++) {
        for (int j = 0; j < (*t).columns; j++) {
            (*t).values[i][j] = (*m_a).values[j][i];
        }
    }
    return t;
}

//Транспонирует комплексную матрицу
void *transpose_matrix_complex(void *a) {
    Matrix *m_a = (Matrix *) a;
    Matrix *t = create_matrix_complex((*m_a).columns, (*m_a).rows);
    for (int i = 0; i < (*t).rows; i++) {
        for (int j = 0; j < (*t).columns; j++) {
            (*t).values[i][j] = (*m_a).values[j][i];
        }
    }
    return t;
}

//Умножает вещественную матрицу на вещественный скаляр
void *mul_scalar_matrix_double(void *a, void *scalar) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            *(double *) (*m_a).values[i][j] = *(double *) scalar * *(double *) (*m_a).values[i][j];
        }
    }
    return m_a;
}

//Умножает вещественную матрицу на комплексный скаляр
void *mul_scalar_matrix_complex(void *a, void *scalar) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            *(double complex *) (*m_a).values[i][j] =
                    *(double complex *) scalar * *(double complex *) (*m_a).values[i][j];
        }
    }
    return m_a;
}

//Перемножает вещественные матрицы
void *mul_matrix_double(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if ((*m_a).columns != (*m_b).rows) {
        printf("It is not possible to multiply matrices!\n");
        return m_a;
    }
    int r = (*m_a).rows, c = (*m_b).columns, n = (*m_a).columns;
    Matrix *m = create_matrix_double(r, c);
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
    Matrix *m = create_matrix_complex(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            *(double complex *) (*m).values[i][j] = (double complex) 0;
            for (int k = 0; k < n; k++) {
                *(double complex *) (*m).values[i][j] +=
                        *(double complex *) (*m_a).values[i][k] * *(double complex *) (*m_b).values[k][j];
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Прибавляет вещественную матрицу
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

//Прибавляет комплексную матрицу
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

//Вычитает матрицу
void *sub_matrix(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if (((*m_a).rows != (*m_b).rows) || ((*m_a).columns != (*m_b).columns)) {
        printf("It is impossible to subtract matrix!\n");
        return m_a;
    }
    double k = -1;
    m_b = (*m_b).mul_scalar(m_b, &k);
    return (*m_a).add_matrix(m_a, m_b);
}