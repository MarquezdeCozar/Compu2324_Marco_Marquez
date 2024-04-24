#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 6.67430e-11
#define c 1.496e11
#define M 1.99e30
#define h 86400 * 100 //* sqrt(G*M/(pow(c,3)))
#define t 365 * 24 * 3600 //* 10  * sqrt(G*M/(pow(c,3)))

double distancia(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void aceleracion(double *ax, double *ay, double *x_pos, double *y_pos, double *masa, double *wx, double *wy, double x, double y, double m, int n_planetas) 
{
    
    double dist, f;

    *wx = *ax * h * 0.5;
    *wy = *ay * h * 0.5;

    *ax = 0;
    *ay = 0;

    for (int i = 0; i < n_planetas; i++) 
    {   
        if (m != masa[i]) 
        {
            dist = distancia(x, y, x_pos[i], y_pos[i]);
            f = G  * masa[i] / pow(dist, 3);
            
            *ax += f * (x_pos[i]-x) ;
            *ay += f * (y_pos[i]-y) ;
        }
    }
}

/* double energia(double *x, double *y, double *vx, double *vy, double *m, int n_planetas)
{
    double e, v;

    e = 0.0;
    v = 0.0;

    for(int i=0; i<n_planetas; i++)
    {   
        for(int j=0; j<n_planetas; j++)
        {
            if(j != i) v += m[i] * m[j] / (distancia(x[i], y[i], x[j], y[j]));
        }
        e += 0.5 * m[i] * (pow(vx[i],2)+pow(vy[i],2)) - v;
    }
    return e;
} */


void pos(double *x, double *y, double *vx, double *vy, double *wx, double *wy, double *ax, double *ay)
{
    *x += *vx * h + 0.5 * *ax * h * h;
    *y += *vy * h + 0.5 * *ay * h * h;

    *wx += *vx + 0.5 * h * *ax;
    *wy += *vy + 0.5 * h * *ay;

}


void veloc(double *x, double *y, double *vx, double *vy, double *wx, double *wy, double *ax, double *ay) 
{
    *vx += *wx + *ax * h * 0.5;
    *vy += *wy + *ay * h * 0.5;
}

int main() 
{   
    FILE *salida = fopen("posiciones.txt", "w");
    FILE *ener = fopen("energia.txt", "w");

    int n_planetas = 9; // Número de planetas usados (contando el sol)
    // double deltaE;


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

    /*for(int i=0; i < n_planetas; i++)
    {
        m[i] = m[i]/M;
        x[i] = x[i]/c;
        y[i] = y[i]/c;
    } */

    // deltaE = energia(x, y, vx, vy, m, n_planetas);


    for(int i=0; i < n_planetas; i++)
    {
        double m0, x0, y0;
        m0 = m[i];
        x0 = x[i];
        y0 = y[i];
        aceleracion(&ax[i], &ay[i], x, y, m, wx, wy, x0, y0, m0, n_planetas);
    }

    for (double paso = 0; paso < t; paso += h) 
    {
        for (int i = 0; i < n_planetas; i++) 
        {
            x[i] = x[i]/c;
            y[i] = y[i]/c; 
            fprintf(salida, "%lf, %lf ", x[i], y[i]);
            fprintf(salida, "\n");
            x[i] = x[i]*c;
            y[i] = y[i]*c;
           /* deltaE -= energia(x, y, vx, vy, m, n_planetas);
            fprintf(ener, "%lf", deltaE);
            fprintf(ener, "\n");*/

        }
        fprintf(salida, "\n");


        for (int i = 0; i < n_planetas; i++) 
        {
            double m0, x0, y0;

            m0 = m[i];
            x0 = x[i];
            y0 = y[i];

            pos(x, y, vx, vy, wx, wy, ax, ay);
            aceleracion(&ax[i], &ay[i], x, y, m, wx, wy, x0, y0, m0, n_planetas);
            veloc(x, y, vx, vy, wx, wy, ax, ay);
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