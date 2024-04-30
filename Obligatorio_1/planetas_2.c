#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 6.67430e-11
#define c 1.496e11
#define M 1.989e30
#define h 0.1
#define t 1000

int n_planetas = 9;

double distancia(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
}

void aceleracion(double x0, double y0, double m0, double *ax, double *ay, double *x, double *y, double *m)
{
    double dist, f;
    *ax = 0;
    *ay = 0;

    for(int i = 0; i < 9; i++)
    {   
        if(m0 != m[i])
        {   
            dist = distancia(x0, y0, x[i], y[i]);
            f = m[i] / pow(dist, 3);
            *ax += f * (x[i] - x0);
            *ay += f * (y[i] - y0);
        }      
    }
    return;
}

void posicion(double *x, double *y, double *ax, double *ay, double *vx, double *vy, double *wx, double *wy)
{
    *x += *vx * h + h * h * *ax * 0.5;
    *y += *vy * h + h * h * *ay * 0.5;

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


int main()
{
    double x0, y0, m0;

    FILE *entrada = fopen("planetas.txt", "w");
    FILE *salida = fopen("posiciones.txt", "w");

    double *x = malloc(n_planetas * sizeof(double));
    double *y = malloc(n_planetas * sizeof(double));
    double *vx = malloc(n_planetas * sizeof(double));
    double *vy = malloc(n_planetas * sizeof(double));
    double *wx = malloc(n_planetas * sizeof(double));
    double *wy = malloc(n_planetas * sizeof(double));
    double *m = malloc(n_planetas * sizeof(double));
    double *ax = malloc(n_planetas * sizeof(double));
    double *ay = malloc(n_planetas * sizeof(double));

    // Datos de los planetas
    x[0] = 0;
    y[0] = 0;
    vx[0] = 0;
    vy[0] = 0;
    m[0] = 1.989e30;
    
    x[1] = 5.791e10;
    y[1] = 0;
    vx[1] = 0;
    vy[1] = 47890;
    m[1] = 3.303e23;

    x[2] = 1.082e11;
    y[2] = 0;
    vx[2] = 0;
    vy[2] = 35030;
    m[2] = 4.869e24;

    x[3] = 1.496e11;
    y[3] = 0;
    vx[3] = 0;
    vy[3] = 29783;
    m[3] = 5.972e24;

    x[4] = 2.2794e11;
    y[4] = 0;
    vx[4] = 0;
    vy[4] = 24130;
    m[4] = 6.421e23;

    x[5] = 7.7833e11;
    y[5] = 0;
    vx[5] = 0;
    vy[5] = 13060;
    m[5] = 1.9e27;

    x[6] = 1.4294e12;
    y[6] = 0;
    vx[6] = 0;
    vy[6] = 9640;
    m[6] = 5.688e26;

    x[7] = 2.8709e12;
    y[7] = 0;
    vx[7] = 0;
    vy[7] = 6810;
    m[7] = 8.686e25;

    x[8] = 4.5043e12;
    y[8] = 0;
    vx[8] = 0;
    vy[8] = 5430;
    m[8] = 1.024e26;

    for(int i=0; i<n_planetas; i++)
    {
        x[i] = x[i]/c;
        m[i] = m[i]/M;
        vy[i] = vy[i] / (sqrt(G * M / c));
    }

    for(int i=0; i<n_planetas; i++)
    {   
        x0 = x[i];
        y0 = y[i];
        m0 = m[i];

        aceleracion(x0, y0, m0, &ax[i], &ay[i], x, y, m);
        
    }

    for(double step = 0; step<t; step+=h)
    {   
        for (int i = 0; i < n_planetas; i++) 
        {   
            fprintf(salida, "%lf, %lf", x[i], y[i]);
            fprintf(salida, "\n");
        }
        fprintf(salida, "\n");


        for(int i = 0; i<n_planetas; i++)
        {
            posicion(&x[i], &y[i], &ax[i], &ay[i], &vx[i], &vy[i], &wx[i], &wy[i]);
            
            x0 = x[i];
            y0 = y[i];
            m0 = m[i];
            
            aceleracion(x0, y0, m0, &ax[i], &ay[i], x, y, m);
            velocidad(&vx[i], &vy[i], &ax[i], &ay[i], &wx[i], &wy[i]);
        }
    }

    fclose(salida);

    free(x);
    free(y);
    free(vx);
    free(vy);
    free(wx);
    free(wy);
    free(m);

    return 0;
}