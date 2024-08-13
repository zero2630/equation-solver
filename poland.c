#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct
{
    size_t pos;
    size_t size;
    char *data;
} stack;


int priority(char c)
{
    switch (c)
    {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '^':
        return 3;
    }
}

void resize_stack(stack *cur_stack)
{
    cur_stack->size += 10;
    cur_stack->data = realloc(cur_stack->data, cur_stack->size * sizeof(char));
    if (cur_stack->data == NULL) {
        printf("\nerror\n");
        exit(1);
    }
}


void push_stack(stack *cur_stack, char value)
{
    if(cur_stack->pos >= cur_stack->size)
    {
        resize_stack(cur_stack);
    }
    cur_stack->data[cur_stack->pos] = value;
    cur_stack->pos++;
}


char pop_stack(stack *cur_stack)
{
    if(cur_stack->pos == 0)
    {
        printf("\nerror\n");
        exit(1);
    }
    cur_stack->pos--;
    return cur_stack->data[cur_stack->pos];
}

char peek_stack(stack *cur_stack)
{
    return cur_stack->data[cur_stack->pos-1];
}

void init_stack(stack *cur_stack)
{
    cur_stack->data = malloc(10*sizeof(char));
    cur_stack->size = 10;
    cur_stack->pos = 0;
}


char *poland(char *equation, size_t l)
{
    char *p_equation = malloc(l * sizeof(l));
    size_t p_size = 0;
    stack p_stack;
    init_stack(&p_stack);

    if(equation[0] != '-') p_equation[p_size++] = '+';

    for(int i=0; i<l; i++)
    {
        if(isdigit(equation[i]) || equation[i] == 'x')
        {
            p_equation[p_size++] = equation[i];
        }
        else if(equation[i] == '(') 
        {
            push_stack(&p_stack, equation[i]);
        }
        else if(equation[i] == ')')
        {
            for(int i=0; i<p_stack.pos; i++)
            {
                p_equation[p_size++] = pop_stack(&p_stack);
            }
        }
        else
        {
            while(p_stack.pos > 0 && priority(equation[i]) <= priority(peek_stack(&p_stack)))
            {
                p_equation[p_size++] = pop_stack(&p_stack);
            }
            push_stack(&p_stack, equation[i]);
        }
    }
    while(p_stack.pos > 0)
    {
        p_equation[p_size++] = pop_stack(&p_stack);
    }
    return p_equation;
}


void main()
{
    char c, equation[100], *p_equation;
    size_t size=0;
    int k, power;

    while ((c=getchar())!='\n')
    {
        equation[size++] = c;
    }
    
    p_equation = poland(equation, size);

    for(int i=0; i<size; i++)
    {
        printf("%c", p_equation[i]);
    }
    printf("\n");

    sscanf(p_equation, "%dx%d^*", &k, &power);
    printf("%d and %d\n", k, power);

}