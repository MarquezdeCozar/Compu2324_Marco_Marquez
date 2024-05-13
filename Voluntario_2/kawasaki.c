#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define n 50
#define T 1.0
#define kB 1.380649e-23


int red[n][n];

void inicializar_red()
{
    for(int i = 1; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            red[i][j] = 1;
        }
    }
    for(int i = 0; i<n; i++)
    {
        red[0][i] = -1;
    }
    return;
}

double minimo(double x)
{
    if(x<1) return x;
    else return 1;
}

void magnetizacion(double *m)
{

    for(int i=0; i<(n/2.0); i++)
    {
        for(int j=0; j<n; j++) m[0] += red[i][j];
        for(int j =0; j<n; j++) m[1] += red[i+n/2][j];
    }
    return;  
}

void densidad(double *d)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++) d[i] += red[i][j];
    }
    return;
}

void kawasaki() //double *E
{
    //E = 0;
    for(int i=0; i<(n*n); i++)
    {
        int j, l, m;
        do
        {
             j = rand() % (n-1);
        }while (j == 0);
        
        int k = rand() % (n);
        
        do
        {
            l = rand() % (n-1);
        } while ((j == l) || (l == 0));

        do
        {
            m = rand() % (n);
        } while (k == m);

        int a, b;

        double deltaE, p, e;        

        deltaE = 2 * (red[j][k] * (red[l+1][m] + red[l-1][m] + 
        red[l][(m+1)%n] + red[l][(m-1+n)%n]) + red[l][m] * (red[j+1][k] + 
        red[j-1][k] + red[j][(k+1)%n] + red[j][(k-1+n)%n]));

        //*E += deltaE;

        p = minimo(1.0/exp(deltaE/T));
        e = 1.0 * rand() / RAND_MAX;

        if(p < e) 
        {
            red[j][k] = -red[j][k];
        }
    }
    return;
}

int main()
{
    int pasos;
    double *m = malloc(2 * sizeof(double));
    //double *energia;
    //energia = 0;

    m[0] = 0.0;
    m[1] = 0.0;

    pasos = 1000;
    inicializar_red();
    
    FILE *salida= fopen("energia.txt", "w");
    FILE *f = fopen("spin.txt", "w");


    for(int h=0; h<pasos; h++)
    {
        //fprintf(salida, "%lf", energia);
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
        magnetizacion(m);
        kawasaki();//energia
    }

    m[0] = m[0]/(n*n*0.5);
    m[1] = m[1]/(n*n*0.5);

    printf("Magnetización media mitad superior : %lf \n", m[0]);
    printf("Magnetización media mitad inferior : %lf \n", m[1]);
    fclose(salida);
    fclose(f);
    
    return 0;
}