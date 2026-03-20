#include "assert.h"
#include "bigint.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
BigInt *factorial(size_t x, BigInt ***arr, size_t *sz, size_t *cap) {
  printf("inside %zu\n", x);
  if (x < *sz)
    return *(*arr + x);
  if (x >= *cap) {
    *arr = realloc(*arr, (x + 1) * sizeof(BigInt *));
    *cap = x + 1;
  }
  assert(*arr && "Unable to realloc");
  BigInt *bigx = intToBigInt(x);
  BigInt *z = factorial(x - 1, arr, sz, cap);
  BigInt *y = mult(z, bigx);
  *(*arr + x) = y;
  *sz = x;
  return y;
}

int main() {
  BigInt **arr = malloc(sizeof(BigInt *));
  arr[0] = intToBigInt(1);
  size_t sz = 1, cap = 1, k = 1;
  /*while (x) {
    scanf("%zu", &x);
    printBigInt(factorial(x, &arr, &sz, &cap));
    printf("\n");
  }*/
  size_t len = 10;
  digit_t *dig = malloc(len * sizeof(digit_t));
  for (size_t i = 0; i < len; i++)
    dig[i] = 0;
  dig[len - 1] = 1;

  BigInt *ZERO = intToBigInt(0);
  BigInt *scaleF = creatBigInt(dig, len);
  BigInt *partialNumer = intToBigInt(44); // 50k-6
  BigInt *numer = intToBigInt(2);         // k! * (2k)!
  BigInt *scaledNumer, *tmp, *term;
  BigInt *denom = intToBigInt(12); // (3k)! * 2^k

  BigInt *sum = intToBigInt(0);
  scaledNumer = mult(numer, partialNumer);

  tmp = scaledNumer;
  scaledNumer = mult(scaledNumer, scaleF);
  freeBigInt(&tmp);

  term = divn(scaledNumer, denom);

  tmp = sum;
  sum = addn(sum, term);
  freeBigInt(&tmp);

  freeBigInt(&term);
  term = intToBigInt(6);

  tmp = term;
  term = mult(term, scaleF);
  freeBigInt(&tmp);

  tmp = sum;
  sum = subn(sum, term);
  freeBigInt(&tmp);
  freeBigInt(&term);

  while (1) {
    k++;

    tmp = denom;
    denom = mult_digit(denom, 3 * k);
    freeBigInt(&tmp);
    tmp = denom;
    denom = mult_digit(denom, 3 * k - 1);
    freeBigInt(&tmp);
    tmp = denom;
    denom = mult_digit(denom, 3 * k - 2);
    freeBigInt(&tmp);
    tmp = denom;
    denom = mult_digit(denom, 2);
    freeBigInt(&tmp);

    tmp = numer;
    numer = mult_digit(numer, k);
    freeBigInt(&tmp);
    tmp = numer;
    numer = mult_digit(numer, 2 * k);
    freeBigInt(&tmp);
    tmp = numer;
    numer = mult_digit(numer, 2 * k - 1);
    freeBigInt(&tmp);

    tmp = partialNumer;
    partialNumer = intToBigInt(50 * k - 6);
    freeBigInt(&tmp);

    scaledNumer = mult(numer, partialNumer);

    tmp = scaledNumer;
    scaledNumer = mult(scaledNumer, scaleF);
    freeBigInt(&tmp);

    term = divn(scaledNumer, denom);

    tmp = sum;
    sum = addn(sum, term);
    freeBigInt(&tmp);
    printBigInt(sum);
    printf("\nk = %zu\n\n", k);
    if (eq(ZERO, term))
      break;
    freeBigInt(&term);
  }
  return 0;
}
