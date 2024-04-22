#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n 4

int red[n][n];

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
    return;
}

int main()
{
    inicializar_red();

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf( "%d", red[i][j]);    
        }
        printf("\n");
    }
    return 0;
}