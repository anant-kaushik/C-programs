/* 
    Queen Board looks like this

        4 x 4

        3  .  Q  .  .  
        2  .  .  .  Q
        1  Q  .  .  . 
        0  .  .  Q  .
           0  1  2  3 
        [  1, 3, 0, 2  ]

    As no column or row can be repeated we can have the solution representation 
    as an array 
*/

#include <stdio.h>
#include <stdlib.h>

const int ALLOW_LOG = 0;

const int CHESS_BOARD_ROW = 8;
const int SOME_BIG_NUMBER = 100000;

int all_perms[SOME_BIG_NUMBER][CHESS_BOARD_ROW];
int all_perms_rows = 0;

const int COMB_SIZE = 2;
int all_combs[SOME_BIG_NUMBER][COMB_SIZE];
int all_combs_size = 0;

int number_of_ways = 0;

/*
    prints array as { a, b }

    array - array to print
    size - size of array
*/
void print_array(int *array, int size)
{
    printf("{");

    if (size == 0)
    {
        printf("");
    }
    else
    {
        for (int i = 0; i < size - 1; i++)
        {
            printf("%d, ", array[i]);
        }
        printf("%d", array[size - 1]);
    }

    printf("}");
}

/*
    prints 2d array as 
    {
      { a, b }
    }

    _2darray - 2d array to print
    row - number of row
    col - number of col
*/
void print_2d_array(int *_2darray, int row, int col)
{
    printf("\n{");
    for (int i = 0; i < row - 1; i++)
    {
        printf("\n  ");
        print_array(_2darray + i * col, col);
        printf(",");
    }
    printf("\n  ");
    print_array(_2darray + (row - 1) * col, col);
    printf("\n}");
}

void insert_array_in_all_combs(int *array, int position)
{
    for (int i = 0; i < COMB_SIZE; i++)
    {
        all_combs[position][i] = array[i];
    }
}

void insert_array_in_all_perms(int *array, int position)
{
    for (int i = 0; i < CHESS_BOARD_ROW; i++)
    {
        all_perms[position][i] = array[i];
    }
}

/*
    Swap two ints
*/
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x   = *y;
    *y   = temp;
}

/*
    array - sorted array to create combination from
    start - start point of the array to fetch data from
    end - end point of the array to fetch data till
    comb_array - output combination array
    comb_index - current index of comb_array
    comb_size - length of combination
*/
void combination(int array[],
                 int start,
                 int end,
                 int comb_array[],
                 int comb_index,
                 int comb_size)
{
    // 1. if index = comb_size print comb_array is complete
    if (comb_index == comb_size)
    {
        if (ALLOW_LOG == 1)
        {
            printf("\nAdding ");
            print_array(comb_array, comb_size);
            printf(" to all_combs");
        }

        insert_array_in_all_combs(comb_array, all_combs_size);
        all_combs_size += 1;
        return;
    }

    // 2. iterate on array[] from start till end.
    //  - stop if we have iterated till the comb_size
    //  - add current value in comb_array.
    //  - recur with start of array insert it in start of comb_array
    //    increase start by 1 and comb_index by 1 and call the function again
    for (int i = start; i <= end; i++)
    {
        comb_array[comb_index] = array[i];
        combination(array, i + 1, end, comb_array, comb_index + 1, comb_size);
    }
}

/*
    array - sorted array to create permutation from
    size - size of array
    start - start point of the array to fetch data from
    end - end point of the array to fetch data till
*/
void permutaion(int *array,
                int size,
                int start,
                int end)
{
    // 1. if start == end print the array
    if (start == end)
    {
        insert_array_in_all_perms(array, all_perms_rows);
        all_perms_rows += 1;
        return;
    }

    // 2. iterate on array[] from start till end.
    //  - the leftmost element if fixed. Create an array for each element to act
    //    as fixed once.
    for (int i = start; i <= end; i++)
    {
        swap(array + start, array + i);
        permutaion(array, size, start + 1, end);
        swap(array + start, array + i);
    }
}
/*
    Brute force method of finding if n queens permutaion on n*n board can exist
    without attacking the other one
*/
int brute_force(int *perm, int size)
{
    // Check if abs distance of queens on x axis is equal to abs distance of
    // queen on y axis. Reject the permutation if true.

    for (int j = 0; j < all_combs_size; j++)
    {
        int x1 = all_combs[j][0];
        int y1 = perm[x1];
        int x2 = all_combs[j][1];
        int y2 = perm[x2];

        if (abs(x1 - x2) == abs(y1 - y2))
        {
            if (ALLOW_LOG == 1)
            {
                printf("\nFound two queens attacking at (%d, %d) and (%d, %d)",
                       x1, x2, y1, y2);
            }
            return 0;
        }
    }
    if (ALLOW_LOG == 1)
    {
        printf("\n");
        print_array(perm, size);
    }
    return 1;
}

void prepare_matrices(int board_size)
{
    int board_columns[board_size];
    for (int i = 0; i < board_size; i++)
    {
        board_columns[i] = i;
    }

    if (ALLOW_LOG == 1)
    {
        printf("\nCreated board_columns array : ");
        print_array(board_columns, board_size);
    }

    // 1. Get all of premutation for n * n board
    permutaion(board_columns, board_size, 0, board_size - 1);
    if (ALLOW_LOG == 1)
    {
        printf("\nCreated permutaions:");
        print_2d_array((int *)all_perms, all_perms_rows, board_size);
    }

    // 2. Get all of combination of 2 index at a time from the array of
    // board_columns
    int comb[COMB_SIZE];
    combination(board_columns, 0, board_size - 1, comb, 0, COMB_SIZE);

    if (ALLOW_LOG == 1)
    {
        printf("\nCreated combinations of board columns : ");
        print_2d_array((int *)all_combs, all_combs_size, COMB_SIZE);
    }
}

int main(void)
{
    printf("Number of ways for %d queen on %d x %d board : ",
           CHESS_BOARD_ROW, CHESS_BOARD_ROW, CHESS_BOARD_ROW);

    prepare_matrices(CHESS_BOARD_ROW);

    for (int j = 0; j < all_perms_rows; j++)
    {
        if (brute_force((int *)all_perms[j], CHESS_BOARD_ROW))
        {
            number_of_ways += 1;
        }
    }

    printf("\n%d\n", number_of_ways);
}
