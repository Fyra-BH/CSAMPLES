#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    double x[8];
    double X[8];
    double a = 0.8;
    for(int i = 0; i < 8; i ++)
    {
        x[i] = pow(a, (double)i);
        printf("x[%d] = %f\n", i, x[i]);
    }

    

    return 0;
}
