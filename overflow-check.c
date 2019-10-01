/*
* Check for overflow case return 1 if the operation wont overflow
*/

#include <limits.h>
#include <stdio.h>

int uadd_ok(unsigned x, unsigned y)
{
    unsigned sum = x + y;
    return sum >= x; // or sum >= y
}

int tadd_ok(int x, int y)
{
    int sum          = x + y;
    int pos_overflow = x >= 0 && y >= 0 && sum < 0;
    int neg_overflow = x < 0 && y < 0 && sum >= 0;
    return !pos_overflow && !neg_overflow;
}

int tsub_ok(int x, int y)
{
    return y == INT_MIN || tadd_ok(x, -y);
}

int tmult_ok(int x, int y)
{
    int64_t prod = x * y;
    return prod == (int)prod;
}

int main()
{
    printf("Check TMAX + TMAX = %d\n", tadd_ok(INT_MAX, INT_MAX));
    printf("Check TMAX + TMIN = %d\n", tadd_ok(INT_MAX, INT_MIN));
    printf("Check TMIN + TMIN = %d\n", tadd_ok(INT_MIN, INT_MIN));
    printf("Check TMIN - TMIN = %d\n", tsub_ok(INT_MIN, INT_MIN));
    printf("Check TMAX - TMIN = %d\n", tsub_ok(INT_MAX, INT_MIN));
    printf("Check -1 - TMIN = %d\n", tsub_ok(-1, INT_MIN));
    return 0;
}