#include <stdio.h>
#include <stdlib.h>

void suma_vectores(double *a, double *b, int dim);

int main(void) {
    int dim;
    printf("Introduce la dimension de los vectores: ");
    scanf("%d", &dim);

    // Asignar memoria para los vectores
    double *a = (double *)malloc(dim * sizeof(double));
    double *b = (double *)malloc(dim * sizeof(double));

    // Leer los valores del vector a
    printf("Introduce los valores del vector a:\n");
    for (int i = 0; i < dim; i++) {
        printf("a[%d]: ", i);
        scanf("%lf", &a[i]);
    }

    // Leer los valores del vector b
    printf("Introduce los valores del vector b:\n");
    for (int i = 0; i < dim; i++) {
        printf("b[%d]: ", i);
        scanf("%lf", &b[i]);
    }

    // Sumar los vectores
    suma_vectores(a, b, dim);

    // Imprimir el resultado
    printf("El resultado de la suma es:\n");
    for (int i = 0; i < dim; i++) {
        printf("%.2f ", a[i]);
    }
    printf("\n");

    // Liberar la memoria asignada para los vectores
    free(a);
    free(b);

    return 0;
}

void suma_vectores(double *a, double *b, int dim) {
    for (int i = 0; i < dim; i++) {
        a[i] += b[i];
    }
}