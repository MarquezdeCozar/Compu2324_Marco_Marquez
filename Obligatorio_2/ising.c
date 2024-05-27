// Programa que simula el modelo de Ising con el método Monte Carlo

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define n 100
#define T 1.5


int red[n][n];

void inicializar_red()
{
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-1; j++)
        {
            if(rand() % 2 == 0) red[i][j] = -1;
            else red[i][j] = 1;
        }
    }
    return;
}

double minimo(double x)
{
    if(x<1) return x;
    else return 1;
}

double montecarlo()
{
    double E;
    E = 0;
    for(int i=0; i<(n*n); i++)
    {
        for(int l=0; l<n; l++)
        {
            red[n-1][l] = red[0][l];
            red[l][n-1] = red[l][0];
        }

        int j = rand() % (n);
        int k = rand() % (n);

        int a, b;

        double deltaE, p, e;

        a = j-1;
        b = k-1;

        if(j < 1) a = n-2;
        else if(j > n-2) j = 0, a = n-2;
        if(k < 1) b = n-2;
        else if(k > n-2) k = 0, b = n-2;

        deltaE = 2 * red[j][k] * (red[j+1][k] + red[a][k] + red[j][k+1] + red[j][b]);
        E -= deltaE;
        p = minimo(exp(-deltaE/T));
        e = ((double) rand() )/ RAND_MAX;

        if(e < p) 
        {
            red[j][k] = -red[j][k];
        }
    }
    return E;
}

int main()
{
    int pasos;
    double energia;
    energia = 0;
    clock_t inicio, final;
    inicio = clock();

    pasos = 1000;
    inicializar_red();
    
    FILE *salida= fopen("energia.txt", "w");
    FILE *f = fopen("spin.txt", "w");


    for(int h=0; h<pasos; h++)
    {
        fprintf(salida, "%lf", energia);
        fprintf(salida, "\n");
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n-1; j++)
            {
                fprintf(f, "%d ,", red[i][j]);
            } 
            fprintf(f, "%d", red[i][n-1]);
            fprintf(f, "\n");
        }
        fprintf(f, "\n");
        energia = montecarlo();
    }

    final = clock();
    printf("Tiempo de ejecución = %lf ", 1.0 * (final-inicio)/CLOCKS_PER_SEC);
    
    return 0;
}