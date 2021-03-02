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

    void *(*mul_matrix)(void *a, void *b);

    void *(*mul_scalar)(void *a, double);

    void *(*add_matrix)(void *a, void *b);

    void *(*subtract_matrix)(void *a, void *b);

    void *(*transpose)(void *a);

} Matrix;

Matrix *create_matrix(int r, int c);

Matrix *creat_identity_double(int s);

Matrix *creat_identity_complex(int s);

Matrix *creat_random_double(int r, int c);

Matrix *creat_random_complex(int r, int c);

void *mul_matrix_double(void *a, void *b);

void *mul_matrix_complex(void *a, void *b);

void *mul_scalar_matrix_double(void *a, double scalar);

void *mul_scalar_matrix_complex(void *a, double scalar);

void *add_matrix_double(void *a, void *b);

void *add_matrix_complex(void *a, void *b);

void *subtract_matrix_double(void *a, void *b);

void *subtract_matrix_complex(void *a, void *b);

void *transpose_matrix(void *a);

#endif