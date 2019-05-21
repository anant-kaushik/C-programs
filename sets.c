/*
    Treat sets as binary numbers

    1100  -> { 3, 2 }

    the indicies become set values 
        
        1  1  0  0
      { 3, 2       } 
*/
#include <stdio.h>
#define BITS sizeof(int) * 8

void print_set(unsigned int binary)
{
    int first_call = 1;

    printf("{");
    for (int i = BITS - 1; i > 0; i--)
    {
        if (0x1 << i & binary)
        {
            if (first_call == 1)
            {
                first_call = 0;
                printf("%d", i);
            }
            else
            {
                printf(", %d", i);
            }
        }
    }

    printf("}");
}

int main(void)
{
    unsigned int x = 0x1 << 31 | 0x1 << 2;
    print_set(x);
    printf("\n");
}