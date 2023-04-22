#ifndef MATRIX_H
#define MATRIX_H

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

#endif /* MATRIX_H */
