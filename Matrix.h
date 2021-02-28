#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

typedef struct Matrix {
    int columns;
    int rows;
    void ***values;
} Matrix;

Matrix *create_matrix(int r, int c);

Matrix *creat_identity_double(int s);

Matrix *creat_identity_complex(int s);

Matrix *creat_random_double(int r, int c);

Matrix *creat_random_complex(int r, int c);

Matrix *mul_matrix_double(Matrix *a, Matrix *b);

Matrix *mul_matrix_complex(Matrix *a, Matrix *b);

Matrix *mul_scalar_matrix_double(Matrix *a, double scalar);

Matrix *mul_scalar_matrix_complex(Matrix *a, double complex scalar);

Matrix *add_matrix_double(Matrix *a, Matrix *b);

Matrix *add_matrix_complex(Matrix *a, Matrix *b);

Matrix *subtract_matrix_double(Matrix *a, Matrix *b);

Matrix *subtract_matrix_complex(Matrix *a, Matrix *b);

Matrix *transpose_matrix(Matrix *a);

#endif