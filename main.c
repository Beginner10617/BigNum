#include "bigint.h"
#include "stdlib.h"
#include "stdio.h"
int main()
{
  digit_t* digx = malloc(
    sizeof(digit_t) * 2
  );
  digx[0] = BASE - 1;
  digx[1] = BASE - 1;

  digit_t* digy = malloc(
    sizeof(digit_t) * 2
  );
  digy[0] = BASE - 1;
  digy[1] = BASE - 1;

  BigInt* x = creatBigInt(digx, 2);
  BigInt* y = creatBigInt(digy, 2);
  BigInt* z = addn(x, y); printf(" ");
  printBigInt(x); printf("\n+");
  printBigInt(y); printf("\n");
  printf("---------------------\n");
  printBigInt(z); printf("\n");
  printf("x > y ? %d\n", gt(x,y));
  printf("x = y ? %d\n", eq(x,y));
  printf("x < y ? %d\n", lt(x,y));
  printf("z > y ? %d\n", gt(z,y));
  printf("z = y ? %d\n", eq(z,y));
  printf("z < y ? %d\n", lt(z,y));
  return 0;
}
