#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char is_zero(double *val)
{
    if(fabs(*val) < 1e-15)
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

size_t solve_quadratic(double *roots, double a, double b, double c)
{
    double discriminant = (b*b)-(4*a*c);

    if(discriminant < 0) return 0;

    else if(is_zero(&discriminant))
    {
        roots[0] = (-1*b)/(2*a);
        return 1;
    }
    else
    {
        roots[0] = (-b+sqrt(discriminant))/(2*a);
        roots[1] = (-b-sqrt(discriminant))/(2*a);
        if(roots[0] > roots[1])
        {
            double buffer = roots[0];
            roots[0] = roots[1];
            roots[1] = buffer;
        }
        return 2;
    }
}

double half_division(double *elements, double x_left, double x_right)
{
    double x_middle, length = fabs(x_right-x_left);
    double innacuracy = 1e-7;
    double left_res, mid_res;

    while(length > innacuracy)
    {
        x_middle = (x_right+x_left)/2;
        left_res = solve_equation(elements, x_left);
        mid_res = solve_equation(elements, x_middle);

        if(mid_res * left_res < 0) x_right = x_middle;
        else if(mid_res == 0) return x_middle;
        else if(left_res == 0) return x_left;
        else x_left = x_middle;
        length = fabs(x_right-x_left);
    }
    return x_middle;
}

void find_root(double *elements, double find_from, double find_to)
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


int max_power(double *elements)
{
    int m_pow = 0;

    for(int i=0; i<10; i++) {
        if(!is_zero(&elements[i])) m_pow = i;
    }
    return m_pow;
}

double *differentiation(double *elements, size_t level)
{

    double *new_elements = calloc(10, sizeof(double));
    for(int i=0; i<10; i++) new_elements[i] = elements[i];

    if(max_power(elements) == level) return new_elements;

    while (max_power(new_elements) > level) {
        for(int i=0; i<9; i++) {
            if(!is_zero(&new_elements[i+1])) new_elements[i] = new_elements[i+1]*(i+1);
            new_elements[i+1] = 0;
        }
    }
    return new_elements;
}

size_t get_roots(double *elements, double *roots, size_t l, size_t level)
{
    double *new_elements = differentiation(elements, level+1);
    double *new_roots = calloc(10, sizeof(double));
    size_t roots_l = 0;
    double left_check, right_check;
    left_check = solve_equation(new_elements, roots[0]-10);
    right_check = solve_equation(new_elements, roots[0]);
    
    {
    int i=1;

    if(is_zero(&right_check)) {
        new_roots[roots_l++] = roots[0];
        i++;
    }
    else if(left_check*right_check < 1e-15) {
        new_roots[roots_l] = half_division(new_elements, roots[0]-10, roots[0]);
        roots_l++;
    }
    for(; i<l; i++)
    {
        left_check = solve_equation(new_elements, roots[i-1]);
        right_check = solve_equation(new_elements, roots[i]);

        if(is_zero(&right_check)) {
            new_roots[roots_l++] = roots[i];
            i++;
        }

        else if(left_check*right_check < 1e-15)
        {
            new_roots[roots_l] = half_division(new_elements, roots[i-1], roots[i]);
            roots_l++;
        }
    }

    left_check = solve_equation(new_elements, roots[l-1]);
    right_check = solve_equation(new_elements, roots[l-1]+10);

    if(!is_zero(&left_check)) { 
        if(left_check*right_check < 1e-15)
        {
            new_roots[roots_l] = half_division(new_elements, roots[l-1], roots[l-1]+10);
            roots_l++;
        }
    }

    }
    
    
    for(int i=0; i<10; i++) roots[i] = new_roots[i];
    free(new_roots);
    free(new_elements);
    return roots_l;
}

void read_block(double *elements, char block[], char length)
{
    char is_positive=1, str_num[10], pos=0;
    int power;
    double k;
    char is_error = 0;

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
        if(i > 6) {
            printf("error: too high/low koefficient in equation\n");
            is_error = 1;
        }
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
        str_num[i] = '\0';
        sscanf(str_num, "%d", &power);
            if(power > 9 || i>2) {
            printf("error: too high power in equation\n");
            is_error = 1;
        }

    if(is_error) exit(1);
    }
    elements[power] += k;
}


int print_equation_roots(char *strline, size_t len) {
    char c, block_counter=0, block[10];
    int a;
    double *elements = calloc(10, sizeof(double));
    double *roots = calloc(10, sizeof(double));
    size_t roots_l;

    {
    int i=0;
    if(strline[0]!='-')
    {
        block[0] = '+';
        block_counter++;
    }
    for (; i<len; i++)
    {
        if((strline[i]=='+' || strline[i]=='-') && i!=0)
        {
            read_block(elements, block, block_counter);
            block_counter = 0;
        }

        block[block_counter] = strline[i];
        block_counter++;

    }
    }
    read_block(elements, block, block_counter);
    block_counter = 0;

    // for(int i=0; i<10; i++) printf("%lf\n", elements[i]);
    // printf("\n");

    if(max_power(elements) == 1) {
        printf("root 1: %lf\n", -elements[0] / elements[1]);
        return 0;
    }

    double *q_elements = differentiation(elements, 2);

    roots_l = solve_quadratic(roots, q_elements[2], q_elements[1], q_elements[0]);


    for(int i=2; i<max_power(elements); i++) {
        roots_l = get_roots(elements, roots, roots_l, i);
    }

    for(int i=0; i<roots_l; i++) {
        printf("root %d: %lf\n", i+1, roots[i]);
    }

    if(roots_l == 0) printf("no roots\n");

    free(roots);
    free(elements);
    // free(q_elements);
    return 0;
}


int main()
{
    FILE *f = fopen("data.txt", "r");
    char *strline = calloc(100, sizeof(char));
    size_t strline_len = 0;
    char c;

    while ((c=getc(f)) != EOF)
    {
        strline[strline_len++] = c;
        if(c == '\n')
        {
            // for(int i=0; i<strline_len; i++) printf("%c", strline[i]);
            // printf("\n");
            print_equation_roots(strline, strline_len-1);
            printf("\n");
            strline_len = 0;
        }
    }

    return 0;
}