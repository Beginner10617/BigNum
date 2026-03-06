#include "bigint.h"
#include "stdio.h"
int main()
{
  BigInt* x = intToBigInt(15);
  printBigInt(x);
  freeBigInt(x);
  return 0;
}
