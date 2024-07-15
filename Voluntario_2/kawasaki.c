#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define n 60
#define T 2.2269


int red[n][n];

//Funciones para inicializar la red de espines manteniendo la primera y
//ultima fila con espin positivo y negativo, respectivamente

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
    for(int i=0; i<n; i++)
    {
        red[0][i] = -1;
        red[n-1][i] = 1;
    }
    return;
}

double energia_media()
{
    double E = 0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            E -= 0.5 * red[i][j] * (red[(i+1)%n][j] + red[(i-1+n)%n][j] +
            red[i][(j+1)%n] + red[i][(j-1+n)%n]);
        }
    }
    return E/(n*n);
}

double minimo(double x)
{
    if(x<1) return x;
    else return 1;
}

void magnetizacion(double *m)
{

    m[0] = 0;
    m[1] = 0;

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
        d[i] = 0;
        for(int j=0; j<n; j++) d[i] += red[i][j];
        d[i] = d[i]/n;
    }
    return;
}

void kawasaki()
{
    for(int i=0; i<(n*n); i++)
    {
        int j, k, l, m;

        j = rand() % n;
        k = rand() % n;

        // Elección de la posición del espín vecino a intercambiar
        // de forma aleatoria

        double a;

        a = (double) rand() / RAND_MAX;
        if(a < 0.25) l = j - 1 , m = k;
        else if(0.25 < a < 0.5) l = j + 1, m = k;
        else if(0.5 < a < 0.75) l = j, m = k-1;
        else l = j, m = k + 1;

        l = (l+n)%n;
        m = (m+n)%n;
        
        //En caso de que el espín sea el mismo, se avanza al siguiente bucle

        if(red[j][k] != red[l][m])
        {

        double deltaE, p, e;      

        // Calculo del cambio en la energía en caso de intercambiar los espines

        int aux = red[j][k];
        red[j][k] = red[l][m];
        red[l][m] = aux;

        deltaE = (red[l][m] * (red[(l+1) % n][m] + red[(l-1+n)%n][m] + 
        red[l][(m+1)%n] + red[l][(m-1+n)%n]) + red[j][k] * (red[(j+1)%n][k] + 
        red[(j-1+n)%n][k] + red[j][(k+1)%n] + red[j][(k-1+n)%n]));

        aux = red[j][k];
        red[j][k] = red[l][m];
        red[l][m] = aux;

        p = minimo(exp(deltaE/T));
        e = ((double) rand() )/ RAND_MAX;

        // Intercambio de espines si se cumple el criterio establecido

        if(e < p) 
        {
            aux = red[j][k];
            red[j][k] = red[l][m];
            red[l][m] = aux;
        }

        for(int i=0; i<n; i++)
        {
            red[0][i] = -1;
            red[n-1][i] = 1;
        }

        }
    }
    return;
}

int main()
{
    int pasos;
    double *m = malloc(2 * sizeof(double));
    double *d = malloc(n * sizeof(double));
    double E;

    clock_t inicio, final;
    inicio = clock();


    m[0] = 0.0;
    m[1] = 0.0;

    pasos = 6000;
    inicializar_red();
    
    FILE *e = fopen("energia.txt", "w");
    FILE *f = fopen("spin.txt", "w");
    FILE *mag = fopen("magnetizacion.txt", "w");
    FILE *den = fopen("densidad.txt", "w");


    for(int h=0; h<pasos; h++)
    {
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

        E = energia_media();
        fprintf(e, "%lf \n", E);
        
        magnetizacion(m);

        m[0] = m[0]/(n*n*0.5);
        m[1] = m[1]/(n*n*0.5);

        fprintf(mag, " %d, %lf, %lf, %lf \n", h, m[0], m[1], m[1]+m[0]);

        kawasaki();
    }

    densidad(d);
    for(int i =0; i<n; i++) fprintf(den, "%d, %lf \n", i, d[i]);

    fclose(den);
    fclose(f);
    fclose(mag);

    final = clock();
    printf("Tiempo de ejecución = %lf \n ", 1.0 * (final-inicio)/CLOCKS_PER_SEC);

    return 0;
}