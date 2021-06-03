#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Matrix.h"

#define put_d(m, i, j, v) *(double *) (*m).values[i][j] = (double) v
#define put_c(m, i, j, v) *(double complex *) (*m).values[i][j] = (double complex) v

void assert(bool status, const char * test_name, const char * text) {
    if (!status) {
        printf("%s failed: %s", test_name, text);
        exit(1);
    }
}

void test_transpose_double() {
    const char * test_name = "test_transpose_double";

    Matrix *m = create_matrix(3, 2, functions_double);
    put_d(m, 0, 0, 1); put_d(m, 0, 1, 2);
    put_d(m, 1, 0, 3); put_d(m, 1, 1, 4);
    put_d(m, 2, 0, 5); put_d(m, 2, 1, 6);

    m = (*m).transpose(m);

    Matrix *target = create_matrix(2, 3, functions_double);
    put_d(target, 0, 0, 1); put_d(target, 0, 1, 3); put_d(target, 0, 2, 5);
    put_d(target, 1, 0, 2); put_d(target, 1, 1, 4); put_d(target, 1, 2, 6);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_transpose_complex() {
    const char * test_name = "test_transpose_complex";

    Matrix *m = create_matrix(3, 2, functions_complex);
    put_c(m, 0, 0, 1); put_c(m, 0, 1, 2);
    put_c(m, 1, 0, 3); put_c(m, 1, 1, 4);
    put_c(m, 2, 0, 5); put_c(m, 2, 1, 6);

    m = (*m).transpose(m);

    Matrix *target = create_matrix(2, 3, functions_complex);
    put_c(target, 0, 0, 1); put_c(target, 0, 1, 3); put_c(target, 0, 2, 5);
    put_c(target, 1, 0, 2); put_c(target, 1, 1, 4); put_c(target, 1, 2, 6);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_mul_scalar_matrix_double() {
    const char * test_name = "test_mul_scalar_matrix_double";

    Matrix *m = create_matrix(3, 3, functions_double);
    put_d(m, 0, 0, 1); put_d(m, 0, 1, 2); put_d(m, 0, 2, 3);
    put_d(m, 1, 0, 4); put_d(m, 1, 1, 5); put_d(m, 1, 2, 6);
    put_d(m, 2, 0, 7); put_d(m, 2, 1, 8); put_d(m, 2, 2, 9);

    double scalar = 2;
    m = (*m).mul_scalar(m, &scalar);

    Matrix *target = create_matrix(3, 3, functions_double);
    put_d(target, 0, 0, 2); put_d(target, 0, 1, 4); put_d(target, 0, 2, 6);
    put_d(target, 1, 0, 8); put_d(target, 1, 1, 10); put_d(target, 1, 2, 12);
    put_d(target, 2, 0, 14); put_d(target, 2, 1, 16); put_d(target, 2, 2, 18);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_mul_scalar_matrix_complex() {
    const char * test_name = "test_mul_scalar_matrix_complex";

    Matrix *m = create_matrix(3, 3, functions_complex);
    put_c(m, 0, 0, 1); put_c(m, 0, 1, 2); put_c(m, 0, 2, 3);
    put_c(m, 1, 0, 4); put_c(m, 1, 1, 5); put_c(m, 1, 2, 6);
    put_c(m, 2, 0, 7); put_c(m, 2, 1, 8); put_c(m, 2, 2, 9);

    double scalar = 2;
    m = (*m).mul_scalar(m, &scalar);

    Matrix *target = create_matrix(3, 3, functions_complex);
    put_c(target, 0, 0, 2); put_c(target, 0, 1, 4); put_c(target, 0, 2, 6);
    put_c(target, 1, 0, 8); put_c(target, 1, 1, 10); put_c(target, 1, 2, 12);
    put_c(target, 2, 0, 14); put_c(target, 2, 1, 16); put_c(target, 2, 2, 18);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_add_matrix_double() {
    const char * test_name = "test_add_matrix_double";

    Matrix *m = create_matrix(3, 3, functions_double);
    put_d(m, 0, 0, 1); put_d(m, 0, 1, 2); put_d(m, 0, 2, 3);
    put_d(m, 1, 0, 4); put_d(m, 1, 1, 5); put_d(m, 1, 2, 6);
    put_d(m, 2, 0, 7); put_d(m, 2, 1, 8); put_d(m, 2, 2, 9);

    m = (*m).add_matrix(m, m);

    Matrix *target = create_matrix(3, 3, functions_double);
    put_d(target, 0, 0, 2); put_d(target, 0, 1, 4); put_d(target, 0, 2, 6);
    put_d(target, 1, 0, 8); put_d(target, 1, 1, 10); put_d(target, 1, 2, 12);
    put_d(target, 2, 0, 14); put_d(target, 2, 1, 16); put_d(target, 2, 2, 18);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_add_matrix_complex() {
    const char * test_name = "test_add_matrix_complex";

    Matrix *m = create_matrix(3, 3, functions_complex);
    put_c(m, 0, 0, 1); put_c(m, 0, 1, 2); put_c(m, 0, 2, 3);
    put_c(m, 1, 0, 4); put_c(m, 1, 1, 5); put_c(m, 1, 2, 6);
    put_c(m, 2, 0, 7); put_c(m, 2, 1, 8); put_c(m, 2, 2, 9);

    m = (*m).add_matrix(m, m);

    Matrix *target = create_matrix(3, 3, functions_complex);
    put_c(target, 0, 0, 2); put_c(target, 0, 1, 4); put_c(target, 0, 2, 6);
    put_c(target, 1, 0, 8); put_c(target, 1, 1, 10); put_c(target, 1, 2, 12);
    put_c(target, 2, 0, 14); put_c(target, 2, 1, 16); put_c(target, 2, 2, 18);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_sub_matrix_double() {
    const char * test_name = "test_sub_matrix_double";

    Matrix *m1 = create_matrix(2, 2, functions_complex);
    put_c(m1, 0, 0, 11); put_c(m1, 0, 1, 12);
    put_c(m1, 1, 0, 13); put_c(m1, 1, 1, 14);

    Matrix *m2 = create_matrix(2, 2, functions_complex);
    put_c(m2, 0, 0, 10); put_c(m2, 0, 1, 10);
    put_c(m2, 1, 0, 10); put_c(m2, 1, 1, 10);

    Matrix *m = (*m1).sub_matrix(m1, m2);

    Matrix *target = create_matrix(2, 2, functions_double);
    put_c(target, 0, 0, 1); put_c(target, 0, 1, 2);
    put_c(target, 1, 0, 3); put_c(target, 1, 1, 4);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_sub_matrix_complex() {
    const char * test_name = "test_sub_matrix_complex";

    Matrix *m1 = create_matrix(2, 2, functions_complex);
    put_c(m1, 0, 0, 11); put_c(m1, 0, 1, 12);
    put_c(m1, 1, 0, 13); put_c(m1, 1, 1, 14);

    Matrix *m2 = create_matrix(2, 2, functions_complex);
    put_c(m2, 0, 0, 10); put_c(m2, 0, 1, 10);
    put_c(m2, 1, 0, 10); put_c(m2, 1, 1, 10);

    Matrix *m = (*m1).sub_matrix(m1, m2);

    Matrix *target = create_matrix(2, 2, functions_double);
    put_c(target, 0, 0, 1); put_c(target, 0, 1, 2);
    put_c(target, 1, 0, 3); put_c(target, 1, 1, 4);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_mul_matrix_double() {
    const char * test_name = "test_mul_matrix_double";

    Matrix *m1 = create_matrix(3, 2, functions_double);
    put_d(m1, 0, 0, 1); put_d(m1, 0, 1, 2);
    put_d(m1, 1, 0, 3); put_d(m1, 1, 1, 4);
    put_d(m1, 2, 0, 5); put_d(m1, 2, 1, 6);

    Matrix *m2 = create_matrix(2, 3, functions_double);
    put_d(m2, 0, 0, 7); put_d(m2, 0, 1, 8); put_d(m2, 0, 2, 9);
    put_d(m2, 1, 0, 10); put_d(m2, 1, 1, 11); put_d(m2, 1, 2, 12);

    Matrix *m = (*m1).mul_matrix(m1, m2);

    Matrix *target = create_matrix(3, 3, functions_double);
    put_d(target, 0, 0, 27); put_d(target, 0, 1, 30); put_d(target, 0, 2, 33);
    put_d(target, 1, 0, 61); put_d(target, 1, 1, 68); put_d(target, 1, 2, 75);
    put_d(target, 2, 0, 95); put_d(target, 2, 1, 106); put_d(target, 2, 2, 117);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}

void test_mul_matrix_complex() {
    const char * test_name = "test_mul_matrix_complex";

    Matrix *m1 = create_matrix(3, 2, functions_complex);
    put_c(m1, 0, 0, 1); put_c(m1, 0, 1, 2);
    put_c(m1, 1, 0, 3); put_c(m1, 1, 1, 4);
    put_c(m1, 2, 0, 5); put_c(m1, 2, 1, 6);

    Matrix *m2 = create_matrix(2, 3, functions_complex);
    put_c(m2, 0, 0, 7); put_c(m2, 0, 1, 8); put_c(m2, 0, 2, 9);
    put_c(m2, 1, 0, 10); put_c(m2, 1, 1, 11); put_c(m2, 1, 2, 12);

    Matrix *m = (*m1).mul_matrix(m1, m2);

    Matrix *target = create_matrix(3, 3, functions_double);
    put_c(target, 0, 0, 27); put_c(target, 0, 1, 30); put_c(target, 0, 2, 33);
    put_c(target, 1, 0, 61); put_c(target, 1, 1, 68); put_c(target, 1, 2, 75);
    put_c(target, 2, 0, 95); put_c(target, 2, 1, 106); put_c(target, 2, 2, 117);

    assert(m->rows == target->rows, test_name, "number of rows");
    assert(m->columns == target->columns, test_name, "number of columns");
    for (int i = 0; i < (*m).rows; i++) {
        for (int j = 0; j < (*m).columns; j++) {
            assert(fabs(*(double *) (*m).values[i][j] - *(double *) (*target).values[i][j]) < 1e-6, test_name, "value");
        }
    }
}