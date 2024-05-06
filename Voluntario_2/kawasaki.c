#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define n 100
#define T 100.0
#define kB 1.380649e-23


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
    for(int i = 0; i<n; i++)
    {
        red[n-1][i] = red[0][i];
        red[i][n-1] = red[i][0];
    }
    red[n-1][n-1] = red[0][0];
}

double minimo(double x)
{
    if(x<1) return x;
    else return 1;
}

/*double calc_energia()
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
}*/

void montecarlo()
{
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


        //red(0,j) = red(n,j) red(n+1,j) = red(1,j) red(i,n) = red(i, 0) 
        //red(i, n+1) = red(i,1)

        a = j-1;
        b = k-1;

        if(j < 1) a = n-2;
        else if(j > n-2) j = 0, a = n-2;
        if(k < 1) b = n-2;
        else if(k > n-2) k = 0, b = n-2;

        deltaE = 2 * red[j][k] * (red[j+1][k] + red[a][k] + red[j][k+1] + red[j][b]);
       
        p = minimo(exp(deltaE/T));
        e = 1.0 * rand() / RAND_MAX;

        if(p < e) 
        {
            red[j][k] = -red[j][k];
        }
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
        //energia = calc_energia();
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