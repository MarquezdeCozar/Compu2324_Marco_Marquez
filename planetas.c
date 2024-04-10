#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 6.67430e-11
#define c 1.496e11

double distancia(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void aceleracion(double *ax, double *ay, double ax_0, double ay_0, double x, double y, double m, double *x_pos, double *y_pos, double *masa, int n_planetas) 
{
    
    double dist, f;

    ax_0 = *ax;
    ay_0 = *ay;

    *ax = 0;
    *ay = 0;

    for (int i = 0; i < n_planetas; i++) 
    {   
        if (m != masa[i]) 
        {
            dist = distancia(x, y, x_pos[i], y_pos[i]);
            f = G * m * masa[i] / pow(dist, 3);
            
            *ax += f * (x_pos[i]-x) / m;
            *ay += f * (y_pos[i]-y) / m;
        }
    }
}

// Algoritmo de Verlet
void verlet(double *x, double *y, double *vx, double *vy, double ax, double ay, double ax_0, double ay_0, double h) 
{

    *x += *vx * h + 0.5 * ax * h * h;
    *y += *vy * h + 0.5 * ay * h * h;
    *vx += (ax_0 + ax) * h * 0.5;
    *vy += (ay_0 + ay) * h * 0.5;

}

int main() 
{
    FILE *salida = fopen("posiciones.txt", "w");

    int n_planetas = 2; // Número de planetas usados

    double *x = malloc(n_planetas * sizeof(double));
    double *y = malloc(n_planetas * sizeof(double));
    double *vx = malloc(n_planetas * sizeof(double));
    double *vy = malloc(n_planetas * sizeof(double));
    double *m = malloc(n_planetas * sizeof(double));

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

    double h = 86400; // Unidad de paso
    double t = 365 * 24 * 3600; // Tiempo total

    for (double paso = 0; paso < t; paso += h) 
    {
        for (int i = 0; i < n_planetas; i++) 
        {
            x[i] =x[i]/c;
            y[i]=y[i]/c;
            fprintf(salida, "%lf, %lf ", x[i], y[i]);
            fprintf(salida, "\n");
            x[i]=x[i]*c;
            y[i]=y[i]*c;
        }
        fprintf(salida, "\n");

        // Actualizar aceleraciones
        for (int i = 0; i < n_planetas; i++) 
        {
            double ax, ay, ax_0, ay_0;
            ax = 0;
            ay = 0;
            aceleracion(&ax, &ay, ax_0, ay_0, x[i], y[i], m[i], x, y, m, n_planetas);
            verlet(&x[i], &y[i], &vx[i], &vy[i], ax, ay, ax_0, ay_0, h);
        }
    }

    fclose(salida);

    free(x);
    free(y);
    free(vx);
    free(vy);
    free(m);

    return 0;
}