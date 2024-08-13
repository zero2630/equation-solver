#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void read_block(int *elements, char block[], char length)
{
    char is_positive=1, str_num[10], pos=0;
    int k, power;

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
        sscanf(str_num, "%d", &k);
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
    char c, block_counter=0, elements_counter=0, block[10];
    int a;
    int *elements = calloc(10, sizeof(int));

    for (int i=0; (c=getchar())!='\n'; i++)
    {
        if((c=='+' || c=='-') && i!=0)
        {
            read_block(elements, block, block_counter);
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
    read_block(elements, block, block_counter);
    block_counter = 0;
    elements_counter++;

    printf("приведённый вид:\n");
    if(elements[0]>0) printf("+%d", elements[0]);
    else if(elements[0]<0) printf("%d", elements[0]);
    if(elements[1]>0) printf("+%dx", elements[1]);
    else if(elements[1]<0) printf("%dx", elements[1]);

    for(int i=2; i<10; i++)
    {
        if(elements[i]>0) printf("+%dx^%d", elements[i], i);
        else if(elements[i]<0) printf("%dx^%d", elements[i], i);
    }
    printf("\n");
        
}