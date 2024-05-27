#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define G 6.67430e-11
#define M_t 5.972e24
#define M_l 7.342e22
#define dist_t_l 3.844e8
#define h 1
#define T_total 1000000
#define pi 3.141592

double w = 2.6618e-6;
double mu = M_l/M_t;
double delta = G * M_t / (dist_t_l*dist_t_l*dist_t_l);


double get_phi(double phi, double r)
{
    return phi / (r*r);
}

double get_pphi(double m, double phi, double r, double t)
{   
    double r_p = sqrt(1 + r*r - 2*r*cos(phi-w*t));
    return - delta * mu * r * sin(phi - w*t)/pow(r_p,3);
}

double get_pr(double pphi, double m, double r, double phi, double t )
{
    double r_p = sqrt(1 + r*r - 2*r*cos(phi-w*t));
    return pphi*pphi/pow(r,3) - delta*(1/(r*r) + mu*(r - cos(phi - w*t))/pow(r_p,3));
}

void runge_kutta(double *k, double *x, double *c, double m, double t)
{
    k[0] = h * (x[1] + c[0]);
    k[1] = h * get_pr(x[3] + c[3], m, x[0] + c[0], x[2] + c[2], t);
    k[2] = h * get_phi(x[2] + c[2], x[0] + c[0]);
    k[3] = h * get_pphi(m, x[2] + c[2], x[0] + c[0], t);	

    return;
}


int main()
{
    double  m, t;

    FILE *salida = fopen("posiciones.txt", "w");

    double *x = malloc(4 * sizeof(double));
    double *c = malloc(4 * sizeof(double));
    double *x_pos = malloc(2 * sizeof(double));
    double *y_pos = malloc(2 * sizeof(double));
    double *k1 = malloc(4 * sizeof(double));
    double *k2 = malloc(4 * sizeof(double));
    double *k3 = malloc(4 * sizeof(double));
    double *k4 = malloc(4 * sizeof(double));

    //Parametros iniciales
    m = 1000;

    x_pos[0] = y_pos[0] = 0;

    x[0] = 6378100/dist_t_l;
    x[1] = 100000/dist_t_l;
    x[2] = 3.141519/2;
    x[3] = 111/pow(dist_t_l,3);


    for(double t = 0; t<T_total; t+=h)
    {
        for(int i=0; i<4; i++)
        {
            c[i] = 0;
        }

        runge_kutta(k1, x, c, m, t);

        for(int i=0; i<4; i++)
        {
            c[i] = k1[i]/2.0;
        }

        runge_kutta(k2, x, c, m, t);

        for(int i=0; i<4; i++)
        {
            c[i] = k2[i]/2.0;
        }

        runge_kutta(k3, x, c, m, t);

        for(int i=0; i<4; i++)
        {
            c[i] = k3[i];
        }

        runge_kutta(k4, x, c, m, t);

        for(int i=0; i<4; i++)
        {
            x[i] = x[i] + (k1[i] + 2*k2[i] + 2*k3[i] + k4[i])/6.0;
        }

        x_pos[1] = cos(w*t);
        y_pos[1] = sin(w*t);

        x_pos[0] = x[0] * cos(x[2]);
        y_pos[0] = x[0] * sin(x[2]);

        //if((int)t%50==0)
        {
            //fprintf(salida, "%lf, %lf \n", 0.0, 0.0);

            for(int i=0; i<4; i++)
            {   
                fprintf(salida, "%lf, %lf, %lf, %lf \n", k1[i], k2[i], k3[i], k4[i]);
                //fprintf(salida, "%lf, %lf \n", x_pos[i], y_pos[i]);
            }
            fprintf(salida, "\n");
        }
    }

    free(x);
    free(x_pos);
    free(y_pos);
    free(c);
    free(k1);
    free(k2);
    free(k3);
    free(k4);

    return 0;
}
