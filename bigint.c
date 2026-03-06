#include "bigint.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"

// helper function
void throwError(const char* err_msg){
  printf("%s\n", err_msg);
  exit(EXIT_FAILURE);
}

// BigInt Constructors
BigInt* creatBigInt(digit_t* digits, size_t len){
  BigInt* out = malloc(sizeof(BigInt));
  if(out==NULL)
    throwError("Unable to allocate space for BigInt - creatBigInt\n");
  
  out->size = len;
  out->cap = pow( 2, ceil(log2(len)) );
  
  if(len == out->cap){
    out->digits = digits;
    return out;
  }
  out->digits = realloc(digits, sizeof(digit_t) * out->cap);
  if(out->digits == NULL)
    throwError("Unable to re-allocate space for BigInt - creatBigInt");
  return out;
}

BigInt* intToBigInt(int x){
  BigInt* out = malloc(sizeof(BigInt));
  if(out==NULL)
    throwError("Unable to allocate space for BigInt - intToBigInt");
  
  out->size = floor(log10(x) / log10(BASE)) + 1;
  out->cap = pow( 2, ceil(log2(out->size)) );
  out->digits = malloc( sizeof(digit_t) * out->cap );
  
  int tmp = x, i = 0;
  while (tmp){
    out->digits[i] = tmp % BASE;
    tmp = tmp / BASE;
    i++;
  }
  
  while (i < out->size){
    out->digits[i] = 0;
    i++;
  }
  return out;
}

// BigInt Destructors
void freeBigInt(BigInt* x){
  free(x->digits);
  free(x);
  x = NULL;
}

// Displaying BigInt (big endian)
void printBigInt(BigInt* x){
  for(int i = x->size - 1; i>=0; i--)
    printf("%d\n", x->digits[i]);
}

// BigInt Operations
