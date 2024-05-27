#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define N 100
#define nciclos N/4
#define lambda 0.8
#define pi 3.14159265
#define T 10000

int main()
{
    FILE *salida = fopen("schrodinger.txt", "w");
    FILE *arcnorma = fopen("norma.txt", "w");
    double stilde, k0tilde, V[N], norma;
    double complex phi[N], alpha[N-1], beta[N-1], chi[N];

    k0tilde = 2 * pi * nciclos / N;
    stilde = 1 /(4 * k0tilde * k0tilde);
    
    for(int j=0; j<N; j++)
    {
        if((j>=(2*N/5))&&(j<=(3*N/5))) V[j] = lambda * k0tilde * k0tilde;
        else V[j] = 0;   
    }   

    for(int j=0; j<N; j++)
    {   
        if(j<(2*N/5)) phi[j] = cexp((I * k0tilde*j)*exp(-8 * (4*j-N)*(4*j-N)/(N*N)));
        else phi[j] = 0;
    }


    phi[0] = 0 + I * 0;
    phi[N-1] = 0 + I * 0;

    alpha[N-2] = 0 + I * 0;

    for(int j=N-3; j>-1; j--)
    {
        alpha[j] = - 1.0 / (alpha[j+1] -2 + 2*I/stilde - V[j+1]);
    }
    
    for(int k=0; k<T; k++)
    {
        norma = 0.0;
        beta[N-2] = 0;
        chi[0] = 0;

        for(int i=N-2; i>0; i--)
        {
            beta[i-1] = ((4 * I * phi[i])/ stilde - beta[i]) /  (alpha[i] -2 + 2*I/stilde - V[i]);
        }

        for(int i=0; i<N-1; i++)
        {
            chi[i+1] = chi[i]*alpha[i] + beta[i];
        }

        for(int i=0; i<N; i++)
        {
            phi[i] = chi[i] - phi[i];
            fprintf(salida, "%d , %lf, %lf \n", i, cabs(phi[i]), V[i]);
            norma += cabs(phi[i]);
        }
        fprintf(salida, "\n");
        fprintf(arcnorma, "%lf \n", norma);
    }

    fclose(salida);
    fclose(arcnorma);

    return 0;    
}
