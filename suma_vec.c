// Programa que suma dos vectores que entren de punteros

void suma_vec(double *a, double *b, int dim) {
    for (int i = 0; i < dim; i++) {
        a[i] += b[i];
    }
}