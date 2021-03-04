#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define create_matrix_double(r, c) create_matrix(r, c, print_value_double, print_matrix, input_value_double, input_matrix, transpose_matrix_double, mul_scalar_matrix_double, mul_matrix_double, add_matrix_double, sub_matrix)
#define create_matrix_complex(r, c) create_matrix(r, c, print_value_complex, print_matrix, input_value_complex, input_matrix, transpose_matrix_complex, mul_scalar_matrix_complex, mul_matrix_complex, add_matrix_complex, sub_matrix)

typedef struct Matrix {
    int rows;
    int columns;
    void ***values;

    void *(*print_value)(void *, int, int);

    void *(*print)(void *);

    void *(*input_value)(void *, int, int);

    void *(*input)(void *);

    void *(*transpose)(void *);

    void *(*mul_scalar)(void *, void *);

    void *(*mul_matrix)(void *, void *);

    void *(*add_matrix)(void *, void *);

    void *(*sub_matrix)(void *, void *);
} Matrix;

void *create_matrix(int r, int c,
                    void *print_value,
                    void *print,
                    void *input_value,
                    void *input,
                    void *transpose,
                    void *mul_scalar,
                    void *mul_matrix,
                    void *add_matrix,
                    void *sub_matrix);

void *create_identity_double(int s);

void *create_identity_complex(int s);

void *create_random_double(int r, int c);

void *create_random_complex(int r, int c);

void *print_value_double(void *m, int r, int c);

void *print_value_complex(void *m, int r, int c);

void *print_matrix(void *a);

void *input_value_double(void *a, int r, int c);

void *input_value_complex(void *a, int r, int c);

void *input_matrix(void *a);

void *transpose_matrix_double(void *a);

void *transpose_matrix_complex(void *a);

void *mul_scalar_matrix_double(void *a, void *scalar);

void *mul_scalar_matrix_complex(void *a, void *scalar);

void *mul_matrix_double(void *a, void *b);

void *mul_matrix_complex(void *a, void *b);

void *add_matrix_double(void *a, void *b);

void *add_matrix_complex(void *a, void *b);

void *sub_matrix(void *a, void *b);

#endif