#include <stdlib.h>


int solve_quadratic(int a, int b, int c, double *roots, size_t *pos)
{
    double discriminant = (b*b)-4*a*c;
    if(discriminant < -1e-15)
    {
        return -1;
    }
    else if((discriminant > 0 && discriminant < 1e-15) || (discriminant < 0 && discriminant > -1e-15) || discriminant == 0)
    {
        roots[(*pos)++] = (-1*b)/(2*a);
        return 0;
    }
    else
    {
        roots[(*pos)++] = (-1*b+sqrt(discriminant))/(2*a);
        printf("%lf\n", sqrt(discriminant));
        roots[(*pos)++] = (-1*b-sqrt(discriminant))/(2*a);
        return 0;
    }
}