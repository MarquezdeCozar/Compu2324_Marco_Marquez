// Programa que simula el comportamiento molecular de un gas

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define L 10  // Lado de la "caja" en la que disponemos las particulas
#define N 20    // Numero de particulas
#define pi 3.1415926
#define h 0.002    // Paso temporal
#define T 100 // Tiempo total

void aceleracion(double x0, double y0, double *x, double *y, double *ax, double *ay)
{
    double deltax, deltay, r;
    *ax = 0;
    *ay = 0;

    for(int i=0; i<N; i++)
    {
        if(x0 != x[i])
        {
            deltax = x[i]-x0;
            deltay = y[i]-y0;

            // Condiciones de contorno periódicas en ambos ejes
            if (deltax > L/2) deltax -= L;
            if (deltax < -L/2) deltax += L;
            if (deltay > L/2) deltay -= L;
            if (deltay < -L/2) deltax += L;
            
            r = sqrt(deltax*deltax + deltay*deltay);


            if(r < 3)
            {
                double a = 24 * (2/pow(r,13) - 1 /pow(r,7));

                if(a < 3000)
                {
                *ax += a * deltax / r;
                *ay += a * deltay / r;
                }


            }
        }
    }
    return;
}

void posicion(double *x, double *y, double *ax, double *ay, double *vx, double *vy, double *wx, double *wy)
{
    *x += *vx * h + h * h * *ax * 0.5;
    *y += *vy * h + h * h * *ay * 0.5;

    //printf("%lf, %lf \n", *ax, *ay);

    if (*x < 0) *x += L;
    if (*x >= L) *x -= L;
    if (*y < 0)  *y += L;
    if (*y >= L) *y -= L;

    *wx = *vx + h * *ax * 0.5;
    *wy = *vy + h * *ay * 0.5;

    return;
}

void velocidad(double *vx, double *vy, double *ax, double *ay, double *wx, double *wy)
{
    *vx = *wx + h * *ax * 0.5;
    *vy = *wy + h * *ay * 0.5;

    return;
}

double energia_cinetica(double *vx, double *vy)
{
    double K = 0;
    for(int i=0; i<N; i++)
    {
        K += 0.5 * (vx[i]*vx[i] + vy[i]*vy[i]);
    }
    return K;
}

double energia_potencial(double *x, double *y)
{
    double P = 0;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(i!=j)
            {
                double r = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);

                if(r < 3) P += 4 * (1/(pow(r,6)) - 1/(pow(r,3)));   
            }
        }
    }
    return P;
}

int main()
{

    FILE *salida = fopen("posiciones.txt", "w");
    FILE *energias = fopen("energias.txt", "w");

    double x0, y0, K, V, E;

    double *x = malloc(N * sizeof(double));
    double *y = malloc(N * sizeof(double));
    double *vx = malloc(N * sizeof(double));
    double *vy = malloc(N * sizeof(double));
    double *wx = malloc(N * sizeof(double));
    double *wy = malloc(N * sizeof(double));
    double *ax = malloc(N * sizeof(double));
    double *ay = malloc(N * sizeof(double));

    //Inicializacion de valores para la velocidad de forma aleatoria,
    // manteniendo el módulo de esta igual a 1

    for(int i=0; i<N; i++)
    {   
        double theta = 2 * pi * rand() / RAND_MAX;
        vx[i] = cos(theta);
        vy[i] = sin(theta);
    }

    // Inicializacion de valores para la posicion de forma semi-aleatoria,
    // disponiendo a las partículas en distintos cuadrantes para evitar
    // fuerzas iniciales muy grandes

    double a = L / sqrt(N);

    for(int i=0; i<N; i++)
    {
        x[i] = a * (i % (int)sqrt(N)) + (double)rand() / RAND_MAX;
        y[i] = a * (i / (int)sqrt(N)) + (double)rand() / RAND_MAX;
    }

    // Calculo de la aceleracion para las posiciones iniciales

    for(int i=0; i<N; i++)
    {
        aceleracion(x[i], y[i], x, y, &ax[i], &ay[i]);
    }

    // Inicio del paso temporal de Verlet

    for(double t=0; t<T; t+=h)
    {
        // Devuelve posiciones a un fichero de texto
        for (int i = 0; i < N; i++) 
        {   
            fprintf(salida, "%lf, %lf", x[i], y[i]);
            fprintf(salida, "\n");
        }
        fprintf(salida, "\n");

        // Paso de Verlet
        for(int i=0; i<N; i++)
        {
            posicion(&x[i], &y[i], &ax[i], &ay[i], &vx[i], &vy[i], &wx[i], &wy[i]);
        }

        for(int i=0; i<N; i++)
        {
            aceleracion(x[i], y[i], x, y, &ax[i], &ay[i]);
        }

        for(int i=0; i<N; i++)
        {
            velocidad(&vx[i], &vy[i], &ax[i], &ay[i], &wx[i], &wy[i]);
        }
        
        // Cálculo de las energías y paso a fichero

        K = energia_cinetica(vx, vy);
        V = energia_potencial(x, y);
        E = K + V;

        fprintf(energias, "% lf, %lf, %lf, %lf \n", t, K, V, E);

    }

    fclose(salida);
    fclose(energias);

    free(x);
    free(y);
    free(vx);
    free(vy);
    free(wx);
    free(wy);
    free(ax);
    free(ay);

    return 0;
}


