#include <stdio.h>
#include <setjmp.h>

jmp_buf exception_buffer;

void throw_exception(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
    longjmp(exception_buffer, 1);
}

struct Matrix {
    int rows;
    int cols;
    double data[128][128];
};

void add(struct Matrix *A, struct Matrix *B, struct Matrix *C);

void multiply(struct Matrix *A, struct Matrix *B, struct Matrix *C);

void scalar_multiply(struct Matrix *A, double scalar, struct Matrix *B);

void invert(struct Matrix *A, struct Matrix *B);

double determinant(struct Matrix *A);

void left_divide(struct Matrix *A, struct Matrix *B, struct Matrix *C);

void right_divide(struct Matrix *A, struct Matrix *B, struct Matrix *C);

void print_matrix(struct Matrix *A);


void add(struct Matrix *A, struct Matrix *B, struct Matrix *C) {
    int i, j;

    if (A->rows != B->rows || A->cols != B->cols) {
        throw_exception("Matrices have different dimensions.");
    }

    C->rows = A->rows;
    C->cols = A->cols;

    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            C->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }
}

void multiply(struct Matrix *A, struct Matrix *B, struct Matrix *C) {
    int i, j, k;
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < B->cols; j++) {
            C->data[i][j] = 0;
            for (k = 0; k < A->cols; k++) {
                C->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }
}

void scalar_multiply(struct Matrix *A, double scalar, struct Matrix *B) {
    int i, j;
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            B->data[i][j] = A->data[i][j] * scalar;
        }
    }
}

void invert(struct Matrix *A, struct Matrix *B) {
    int i, j, k;
    double temp;
    struct Matrix temp_matrix = *A;
    B->rows = A->rows;
    B->cols = A->cols;
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            if (i == j) {
                B->data[i][j] = 1;
            } else {
                B->data[i][j] = 0;
            }
        }
    }
    for (i = 0; i < A->rows; i++) {
        temp = temp_matrix.data[i][i];
        for (j = 0; j < A->cols; j++) {
            temp_matrix.data[i][j] /= temp;
            B->data[i][j] /= temp;
        }
        for (j = 0; j < A->rows; j++) {
            if (i != j) {
                temp = temp_matrix.data[j][i];
                for (k = 0; k < A->cols; k++) {
                    temp_matrix.data[j][k] -= temp * temp_matrix.data[i][k];
                    B->data[j][k] -= temp * B->data[i][k];
                }
            }
        }
    }
}

double determinant(struct Matrix *A) {
    int i, j, k, n;
    double det = 1, temp;
    struct Matrix temp_matrix = *A;
    n = A->rows;
    for (i = 0; i < n; i++) {
        if (temp_matrix.data[i][i] == 0) {
            for (j = i + 1; j < n; j++) {
                if (temp_matrix.data[j][i] != 0) {
                    for (k = 0; k < n; k++) {
                        temp = temp_matrix.data[i][k];
                        temp_matrix.data[i][k] = temp_matrix.data[j][k];
                        temp_matrix.data[j][k] = temp;
                    }
                    det *= -1;
                    break;
                }
            }
            if (j == n) {
                return 0;
            }
        }
        det *= temp_matrix.data[i][i];
        for (j = i + 1; j < n; j++) {
            temp = temp_matrix.data[j][i] / temp_matrix.data[i][i];
            for (k = i; k < n; k++) {
                temp_matrix.data[j][k] -= temp * temp_matrix.data[i][k];
            }
        }
    }
    return det;
}

void left_divide(struct Matrix *A, struct Matrix *B, struct Matrix *C) {
    struct Matrix A_inv;
    invert(A, &A_inv);
    multiply(&A_inv, B, C);
}

void right_divide(struct Matrix *A, struct Matrix *B, struct Matrix *C) {
    struct Matrix B_inv;
    invert(B, &B_inv);
    multiply(A, &B_inv, C);
}

void print_matrix(struct Matrix *A) {
    int i, j;
    for (i = 0; i < A->rows; i++) {
        for (j = 0; j < A->cols; j++) {
            printf("%.2f ", A->data[i][j]);
        }
        printf("\n");
    }
}