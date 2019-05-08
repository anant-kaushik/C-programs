#include <stdio.h>

int main(void)
{
  for (int i = 100000; i < 101000; i++)
  {
    if (i % 9175 == 0)
    {
      printf("Found i %d", i);
      break;
    }
  }
}