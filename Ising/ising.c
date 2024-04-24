// Programa que simula el modelo de Ising con el método Monte Carlo

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define n 5
#define T 4
#define kB 1.380649e-23


int red[n][n];

void inicializar_red()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(rand() % 2 == 0) red[i][j] = -1;
            else red[i][j] = 1;
        }
    }
}

double minimo(double x, double y)
{
    if(x<y) return x;
    else return y;
}

double calc_energia()
{
    double energia;
    energia = 0.0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            energia += red[i][j] * (red[i][j+1] + red[i][j-1] + red[i+1][j] + red[i-1][j]);
        }
    }
    return energia/2.0;
}

void montecarlo()
{
    for(int i=0; i<(n*n); i++)
    {
        int j = rand() % (n+1);
        int k = rand() % (n+1);

        int a, b, c, d;

        double deltaE, p, e;
    

        a = j+1;
        b = j-1;
        c = k+1;
        d = k-1;

        if(j=n-1) a = 0;
        else if (j = 0) b = n-1;
        else if (k = n-1) c = 0;
        else if (k=0) d = n-1;

        deltaE = 2 * red[j][k] * (red[a][k] + red[b][k] + red[j][c] + red[j][d]);
        p = minimo(1,exp(-deltaE/T));
        e = rand();
        if(p < e) red[j][k] = -red[j][k];
    }
}

int main()
{
    int pasos;
    double energia;

    pasos = 100;
    inicializar_red();
    
    FILE *salida= fopen("energia.txt", "w");
    FILE *f = fopen("spin.txt", "w");


    for(int h=0; h<pasos; h++)
    {
        energia = calc_energia();
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
        montecarlo();
    }
    
    return 0;
}