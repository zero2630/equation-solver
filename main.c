#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char is_zero(double *val)
{
    if((*val > 0 && *val < 1e-15) || (*val < 0 && *val > -1e-15) || *val == 0)
    {
        return 1;
    }
    return 0;
}

double power(double val, int val_power)
{
    double new_val = val;

    if(val_power==0) return 1;
    else if(val_power==1) return val;
    else
    {
        for(int i=0; i<val_power-1; i++)
        {
            new_val *= val;
        }
    }
    return new_val;
}

double solve_equation(double *elements, double val)
{
    double answer=0;

    for(int i=0; i<10; i++)
    {
        if(!is_zero(&elements[i])) answer += elements[i] * power(val, i);
    }

    return answer;
}

double half_division(double *elements, double x_left, double x_right)
{
    double x_middle, length = fabs(x_right-x_left);

    while(length > 1e-7)
    {
        x_middle = (x_right+x_left)/2;
        if(solve_equation(elements, x_middle) * solve_equation(elements, x_left) <= 0) x_right = x_middle;
        else x_left = x_middle;
        length = fabs(x_right-x_left);
    }
    return x_middle;
}

void find_roots(double *elements, double find_from, double find_to)
{
    double segments[20];
    size_t segments_size = 0;
    double step = find_from;
    double buffer = solve_equation(elements, step);
    double result;

    for(int i=1; step<find_to;)
    {
        step += 0.1;
        result = solve_equation(elements, step);
        if(result > 0 && buffer < 0 || result < 0 && buffer > 0)
        {
            segments[i] = step;
            segments[i-1] = step-0.1;
            i += 2;
            segments_size = i;
        }
        buffer = result;
    }

    if(is_zero(&elements[0])) printf("root: 0\n");
    for(int i=0; i<segments_size-1; i+=2)
    {
        printf("root: %lf\n", half_division(elements, segments[i], segments[i+1]));
    }
}

void read_block(double *elements, char block[], char length)
{
    char is_positive=1, str_num[10], pos=0;
    int power;
    double k;

    if(block[pos]=='-') is_positive=0;
    pos++;
    if(block[pos]!='x')
    {
        size_t i=0;
        while(pos<length && block[pos]!='x')
        {
            str_num[i++] = block[pos++];
        }
        str_num[i++] = '\0';
        sscanf(str_num, "%lf", &k);
        if(!is_positive) k *= -1;
    }

    else
    {
        if(is_positive) k = 1;
        else k = -1;
    }

    if(pos == length) power = 0;
    else if(pos==length-1) power = 1;
    else
    {
        char i=0;
        pos += 2;
        while(pos<length && block[pos]!='x')
        {
            str_num[i] = block[pos];
            pos++;
            i++;
        }
        sscanf(str_num, "%d", &power);
    }
    elements[power] += k;
}


void main()
{
    char c, block_counter=0, block[10];
    int a;
    double *elements = calloc(10, sizeof(int)), *roots = calloc(10, sizeof(int));

    for (int i=0; (c=getchar())!='\n'; i++)
    {
        if((c=='+' || c=='-') && i!=0)
        {
            read_block(elements, block, block_counter);
            block_counter = 0;
        }
        if(i==0 && c!='-')
        {
            block[i] = '+';
            block_counter++;
            i++;
        }

        block[block_counter] = c;
        block_counter++;

    }
    read_block(elements, block, block_counter);
    block_counter = 0;

    // printf("приведённый вид:\n");
    // if(elements[0]>1e-15) printf("+%.2lf", elements[0]);
    // else if(elements[0]<-1e-15) printf("%.2lf", elements[0]);
    // if(elements[1]>1e-15) printf("+%.2lfx", elements[1]);
    // else if(elements[1]<-1e-15) printf("%.2lfx", elements[1]);

    // for(int i=2; i<10; i++)
    // {
    //     if(elements[i]>1e-15) printf("+%.2lfx^%d", elements[i], i);
    //     else if(elements[i]<-1e-15) printf("%.2lfx^%d", elements[i], i);
    // }
    // printf("\n");

    find_roots(elements, -10, 10);
        
}