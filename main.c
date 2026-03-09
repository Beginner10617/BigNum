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
  digy[1] = BASE - 5;

  BigInt* x = creatBigInt(digx, 2);
  BigInt* y = creatBigInt(digy, 2);
  BigInt* z1 = addn(x, y); 
  BigInt* z2 = subn(x, y);
  BigInt* z3 = mult(x, y);
  printf(" ");
  printBigInt(x); printf("\n+");
  printBigInt(y); printf("\n");
  printf("------------------\n");
  printBigInt(z1); printf("\n\n ");
  printBigInt(x); printf("\n-");
  printBigInt(y); printf("\n");
  printf("------------------\n");
  printBigInt(z2); printf("\n\n ");
  printBigInt(x); printf("\nx");
  printBigInt(y); printf("\n");
  printf("------------------\n");
  printBigInt(z3); printf("\n\n");

  return 0;
}
