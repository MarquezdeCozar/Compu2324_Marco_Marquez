#include <stdio.h>
#include <stdlib.h>

#define G 6.67430e-11
#define c 1.496e11
#define M 1.99e30
#define h 86400 * 100 * sqrt(G*M/(pow(c,3)))
#define t 365 * 24 * 3600 * 10 * sqrt(G*M/(pow(c,3)))

int main()
{
    printf("%lf", h);
    double x = 86400 * 100 * sqrt(G*M/(pow(c,3)));
    printf("%lf", x);
    return 0;
}