#include <stdio.h>

char arr[] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!', '\0' } ;

void arrchar1(char *arr, int pos)
{
  printf("[%d]: %c\n", pos, arr[pos] );
}

void arrchar2(char *arr, int pos)
{
  printf("[%d]: %c\n", pos, *(arr + pos));
}

int main()
{
  printf("size of arr: %d\n", (int) sizeof(arr));
  arrchar1(arr, 6);
  arrchar2(arr, 6);
  return 0;
}