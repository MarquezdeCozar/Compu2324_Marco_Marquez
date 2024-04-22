#include <stdio.h>
#include <stdlib.h>

void suma_vec(double *a, double *b, int dim);

int main(void) {
    int dim;
    printf("Introduce la dimension de los vectores: ");
    scanf("%d", &dim);

    double *a = (double *)malloc(dim * sizeof(double));
    double *b = (double *)malloc(dim * sizeof(double));

    printf("Introduce los valores del vector a:\n");
    for (int i = 0; i < dim; i++) {
        printf("a[%d]: ", i);
        scanf("%lf", &a[i]);
    }

    printf("Introduce los valores del vector b:\n");
    for (int i = 0; i < dim; i++) {
        printf("b[%d]: ", i);
        scanf("%lf", &b[i]);
    }

    suma_vec(a, b, dim);

    printf("El resultado de la suma es:\n");
    for (int i = 0; i < dim; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");

    free(a);
    free(b);

    return 0;
}

void suma_vec(double *a, double *b, int dim) {
    for (int i = 0; i < dim; i++) {
        a[i] += b[i];
    }
}