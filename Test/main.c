#include <stdio.h>
#include "matrix.h"

int main() {
    struct Matrix A = {2, 2, {{1, 2}, {3, 4}}};
    struct Matrix B = {2, 2, {{5, 6}, {7, 8}}};
    struct Matrix C;


    add(&A, &B, &C);



    printf("A + B =\n");
    print_matrix(&A);

    return 0;
}
