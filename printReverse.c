#include <stdio.h>

void printReverse(char *str)
{
    if (!*str)
        return;
    printReverse(str + 1);
    putchar(*str);
}

int main()
{
    printReverse("hi ! i am anant \n");
}