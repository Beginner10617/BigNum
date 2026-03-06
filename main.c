#include "bigint.h"
#include "stdio.h"
int main()
{
  BigInt* x = intToBigInt(15);
  printBigInt(x);
  freeBigInt(&x);
  if(x==NULL)
    printf("Memory for x freed!\n");
  printf("%p\n", x);
  return 0;
}
