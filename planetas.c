#include <stdio.h>
#include <math.h>

#define G 6.67430e-11
#define c 1.496e11
double distancia(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void aceleracion(double *ax, double *ay, double x, double y, double m, double *x_pos, double *y_pos, double *mass, int n_planetas) 
{
    
    double dist, f;

    *ax = 0;
    *ay = 0;
    for (int i = 0; i < n_planetas; i++) 
    {
        if (x != x_pos[i] || y != y_pos[i]) 
        {
            dist = distancia(x, y, x_pos[i], y_pos[i]);
            f = G * m * mass[i] / pow(dist, 3);
            
            *ax += f * (x_pos[i]-x) / m;
            *ay += f * (y_pos[i]-y) / m;
        }
    }
}

// Algoritmo de Verlet
void verlet(double *x, double *y, double *vx, double *vy, double ax, double ay, double h) 
{
    double x_temp, y_temp; 
 
    x_temp = *x;
    y_temp = *y;

    *x += *vx * h + 0.5 * ax * h * h;
    *y += *vy * h + 0.5 * ay * h * h;
    *vx += ax * h;
    *vy += ay * h;

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

    x[1] = 1.496e11;
    y[1] = 0;
    vx[1] = 0;
    vy[1] = 29783;
    m[1] = 5.972e24;

    double h = 86400; // Unidad de paso
    double t = 365 * 24 * 3600; // Tiempo total

    for (double paso = 0; paso < t; paso += h) 
    {
        for (int i = 0; i < n_planetas; i++) 
        {
            x[i] = x[i]/c;
            y[i] = y[i]/c;
            fprintf(salida, "%lf, %lf ", x[i], y[i]);
            fprintf(salida, "\n");
            x[i]=x[i]*c;
            y[i]=y[i]*c;
        }
        fprintf(salida, "\n");

        // Actualizar aceleraciones
        for (int i = 0; i < n_planetas; i++) 
        {
            double ax, ay;
            aceleracion(&ax, &ay, x[i], y[i], m[i], x, y, m, n_planetas);
            verlet(&x[i], &y[i], &vx[i], &vy[i], ax, ay, h);
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