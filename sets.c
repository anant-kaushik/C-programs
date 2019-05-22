/*
    Treat sets as binary numbers

    1100  -> { 3, 2 }

    the indicies become set values 
        
        1  1  0  0
      { 3, 2       } 
*/
#include <stdio.h>
#define BITS sizeof(short) * 8

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

short set_intersetion(unsigned short x, unsigned short y)
{
    return x & y;
}

short set_union(unsigned short x, unsigned short y)
{
    return x | y;
}

short set_sym_diff(unsigned short x, unsigned short y)
{
    return x ^ y;
}

short set_complement(unsigned short x)
{
    return ~x;
}

int main(void)
{
    unsigned short x = 0x1 << 6 | 0x1 << 5 | 0x1 << 3 | 0x1 << 0;
    unsigned short y = 0x1 << 6 | 0x1 << 4 | 0x1 << 2 | 0x1 << 0;

    printf("We have the following sets:\n1. ");
    print_set(x);
    printf("\n2. ");
    print_set(y);

    printf("\nSet intersection is - ");
    print_set(set_intersetion(x, y));

    printf("\nSet union is - ");
    print_set(set_union(x, y));

    printf("\nSymmetric difference is - ");
    print_set(set_sym_diff(x, y));

    printf("\n1's complement is - ");
    print_set(set_complement(x));
    printf("\n2's complement is - ");
    print_set(set_complement(y));

    printf("\n");
}
