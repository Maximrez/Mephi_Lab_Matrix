#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define functions_double print_value_double, print_matrix, input_value_double, put_zero_double, put_one_double, input_matrix, transpose_matrix, add_values_double, mul_values_double, mul_scalar_matrix, mul_matrix, add_matrix, sub_matrix
#define functions_complex print_value_complex, print_matrix, input_value_complex, put_zero_complex, put_one_complex, input_matrix, transpose_matrix, add_values_complex, mul_values_complex, mul_scalar_matrix, mul_matrix, add_matrix, sub_matrix
#define functions_format(m) (*m).print_value, (*m).print, (*m).input_value, (*m).put_zero, (*m).put_one, (*m).input, (*m).transpose, (*m).add_values, (*m).mul_values, (*m).mul_scalar, (*m).mul_matrix, (*m).add_matrix, (*m).sub_matrix
#define function_list void *print_value, void *print, void *input_value, void *put_zero, void *put_one, void *input, void *transpose, void *add_values, void *mul_values, void *mul_scalar, void *mul_matrix, void *add_matrix, void *sub_matrix

typedef struct Matrix {
    int rows;
    int columns;
    void ***values;

    void *(*print_value)(void *, int, int);

    void *(*print)(void *);

    void *(*input_value)(void *, int, int);

    void *(*put_zero)(void *, int, int);

    void *(*put_one)(void *, int, int);

    void *(*input)(void *);

    void *(*transpose)(void *);

    void *(*add_values)(void *, void *);

    void *(*mul_values)(void *, void *);

    void *(*mul_scalar)(void *, void *);

    void *(*mul_matrix)(void *, void *);

    void *(*add_matrix)(void *, void *);

    void *(*sub_matrix)(void *, void *);
} Matrix;

void *create_matrix(int r, int c, function_list);

void *create_identity(int s, function_list);

void *create_random_double(int r, int c);

void *create_random_complex(int r, int c);

void *print_value_double(void *m, int r, int c);

void *print_value_complex(void *m, int r, int c);

void *print_matrix(void *a);

void *input_value_double(void *a, int r, int c);

void *input_value_complex(void *a, int r, int c);

void *put_zero_double(void *a, int i, int j);

void *put_zero_complex(void *a, int i, int j);

void *put_one_double(void *a, int i, int j);

void *put_one_complex(void *a, int i, int j);

void *input_matrix(void *a);

void *transpose_matrix(void *a);

void *add_values_double(void *a, void *b);

void *add_values_complex(void *a, void *b);

void *mul_values_double(void *a, void *b);

void *mul_values_complex(void *a, void *b);

void *mul_scalar_matrix(void *a, void *scalar);

void *mul_matrix(void *a, void *b);

void *add_matrix(void *a, void *b);

void *sub_matrix(void *a, void *b);

#endif