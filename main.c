#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct element
{
    int k;
    int n;
};

int stepen(int num, int n)
{
    if(n==0) return 1;
    int new_num = num;

    for(int i=0; i<n-1; i++)
    {
        new_num *= num;
    }

    return new_num;
}

int str_to_int(char str_num[], char length, char is_positive)
{
    int num = 0;

    for(int i=0; i<length; i++)
    {
        num += (str_num[i]-'0')*stepen(10, length-i-1);
    }

    if(is_positive==1)
        return num;
    return -num;
}


struct element read_block(char block[], char length)
{
    char is_positive=1, str_num[10], pos=0;
    struct element elem;

    if(block[pos]=='-') is_positive=0;
    pos++;
    if(block[pos]!='x')
    {
        char i=0;
        while(pos<length && block[pos]!='x')
        {
            str_num[i] = block[pos];
            pos++;
            i++;
        }
        elem.k = str_to_int(str_num, i, is_positive);
    }

    else
    {
        if(is_positive) elem.k = 1;
        else elem.k = -1;
    }

    if(pos == length)
    {
        elem.n = 0;
        return elem;
    }
    else if(pos==length-1)
    {
        elem.n = 1;
        return elem;
    }
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
        elem.n = str_to_int(str_num, i, 1);
        return elem;
    }
}


void main()
{
    char c, block_counter=0, elements_counter=0, block[10];
    int a;
    struct element elements[10];

    for (int i=0; (c=getchar())!='\n'; i++)
    {
        if((c=='+' || c=='-') && i!=0)
        {
            elements[elements_counter] = read_block(block, block_counter);
            block_counter = 0;
            elements_counter++;
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
    elements[elements_counter] = read_block(block, block_counter);
    block_counter = 0;
    elements_counter++;

    for(int i=0; i<elements_counter; i++)
    {
        printf("%d-й член уравнения: k=%d; n=%d\n", i+1, elements[i].k, elements[i].n);
    }
        
}