#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <time.h>

const int E = 20, P = 0; //Константы рандома (модуль числа и количество цифр после запятой)

//Выделяет память под матрицу и создаёт её
void *create_matrix(int r, int c, function_list) {

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
    (*m).put_zero = put_zero;
    (*m).put_one = put_one;
    (*m).input = input;
    (*m).transpose = transpose;
    (*m).add_values = add_values;
    (*m).mul_values = mul_values;
    (*m).mul_scalar = mul_scalar;
    (*m).mul_matrix = mul_matrix;
    (*m).add_matrix = add_matrix;
    (*m).sub_matrix = sub_matrix;
    return m;
}

// Создаёт единичную матрицу
void *create_identity(int s, function_list) {
    Matrix *m = create_matrix(s, s, print_value, print, input_value, put_zero, put_one, input, transpose, add_values,
                              mul_values, mul_scalar, mul_matrix, add_matrix, sub_matrix);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (i == j) {
                m = (*m).put_one(m, i, j);
            } else {
                m = (*m).put_zero(m, i, j);
            }
        }
    }
    return m;
}

//Создаёт случайно заполненную вещественную матрицу
void *create_random_double(int r, int c) {
    srand(time(0));
    int d = (int) pow(10, P);
    Matrix *m = create_matrix(r, c, functions_double);
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
    Matrix *m = create_matrix(r, c, functions_complex);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double r1 = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
            double r2 = (double) (rand() % (E * d) - ((double) E * d / 2)) / d;
            *(double complex *) (*m).values[i][j] = r1 + r2 * I;
        }
    }
    return m;
}

//Выводит на экран элемент вещественной матрицы
void *print_value_double(void *a, int r, int c) {
    Matrix *m_a = (Matrix *) a;
    printf("%.1lf", *(double *) (*m_a).values[r][c]);
}

//Выводит на экран элемент комплексной матрицы
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

//Выводит на экран матрицу
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

//Ввод с клавиатуры элемента вещественной матрицы
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

//Делает элемент вещественной матрицы равным нулю
void *put_zero_double(void *a, int i, int j) {
    Matrix *m_a = (Matrix *) a;
    *(double *) (*m_a).values[i][j] = (double) 0;
    return m_a;
}

//Делает элемент комплексной матрицы равным нулю
void *put_zero_complex(void *a, int i, int j) {
    Matrix *m_a = (Matrix *) a;
    *(double complex *) (*m_a).values[i][j] = (double complex) 0;
    return m_a;
}

//Делает элемент вещественной матрицы равным единице
void *put_one_double(void *a, int i, int j) {
    Matrix *m_a = (Matrix *) a;
    *(double *) (*m_a).values[i][j] = (double) 1;
    return m_a;
}

//Делает элемент комплексной матрицы равным нулю
void *put_one_complex(void *a, int i, int j) {
    Matrix *m_a = (Matrix *) a;
    *(double complex *) (*m_a).values[i][j] = (double complex) 1;
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

//Транспонирует матрицу
void *transpose_matrix(void *a) {
    Matrix *m_a = (Matrix *) a;
    Matrix *t = create_matrix((*m_a).columns, (*m_a).rows, functions_format(m_a));

    for (int i = 0; i < (*t).rows; i++) {
        for (int j = 0; j < (*t).columns; j++) {
            (*t).values[i][j] = (*m_a).values[j][i];
        }
    }
    return t;
}

//Складывает вещественные числа
void *add_values_double(void *a, void *b) {
    double *r = (double *) malloc(sizeof(double));
    *r = *(double *) a + *(double *) b;
    return r;
}

//Складывает комплексные числа
void *add_values_complex(void *a, void *b) {
    double complex *r = (double complex *) malloc(sizeof(double complex));
    *r = *(double complex *) a + *(double complex *) b;
    return r;
}

//Перемножает вещественные числа
void *mul_values_double(void *a, void *b) {
    double *r = (double *) malloc(sizeof(double));
    *r = *(double *) a * *(double *) b;
    return r;
}

//Перемножает комплексные числа
void *mul_values_complex(void *a, void *b) {
    double complex *r = (double complex *) malloc(sizeof(double complex));
    *r = *(double complex *) a * *(double complex *) b;
    return r;
}

//Умножает матрицу на скаляр
void *mul_scalar_matrix(void *a, void *scalar) {
    Matrix *m_a = (Matrix *) a;
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            (*m_a).values[i][j] = (*m_a).mul_values((*m_a).values[i][j], scalar);
        }
    }
    return m_a;
}

//Перемножает матрицы
void *mul_matrix(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if ((*m_a).columns != (*m_b).rows) {
        printf("It is not possible to multiply matrices!\n");
        return m_a;
    }
    int r = (*m_a).rows, c = (*m_b).columns, n = (*m_a).columns;
    Matrix *m = create_matrix(r, c, functions_format(m_a));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            m = (*m).put_zero(m, i, j);
            for (int k = 0; k < n; k++) {
                (*m).values[i][j] = (*m).add_values((*m).values[i][j],
                                                    (*m).mul_values((*m_a).values[i][k], (*m_b).values[k][j]));
            }
        }
    }
    printf("Operation completed successfully!\n");
    return m;
}

//Прибавляет матрицу
void *add_matrix(void *a, void *b) {
    Matrix *m_a = (Matrix *) a;
    Matrix *m_b = (Matrix *) b;
    if (((*m_a).rows != (*m_b).rows) || ((*m_a).columns != (*m_b).columns)) {
        printf("It is impossible to add matrix!\n");
        return m_a;
    }
    for (int i = 0; i < (*m_a).rows; i++) {
        for (int j = 0; j < (*m_a).columns; j++) {
            (*m_a).values[i][j] = (*m_a).add_values((*m_a).values[i][j], (*m_b).values[i][j]);
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