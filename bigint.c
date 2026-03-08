#include "bigint.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include "assert.h"
// Display colors for errors and warnings
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

// helper function
void throwError(const char* err_msg){
  printf(ERROR "%s\n" COLOR_RESET, err_msg);
  exit(EXIT_FAILURE);
}

void throwWarning(const char* warn_msg){
  printf(WARNING "%s\n" COLOR_RESET, warn_msg);
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
void freeBigInt(BigInt** x){
  if(x && *x){
    free( (*x)->digits );
    free(*x);
    *x = NULL;
    return;
  }
  throwWarning("Trying to free NULL pointer - freeBigInt");
}

// Displaying BigInt (big endian)
void printBigInt(BigInt* x){
  for(size_t i = x->size - 1; 
  i>=0; i--){
    if(i != x->size-1 
    && x->digits[i]){
      int lz = floor(log10(x->digits[i]))+1;
      lz = DIG_LEN - lz;
      for(int j=0; j<lz; j++)
        printf("0");
    }
    else if(x->digits[i]==0
    && i!= x->size-1){
      for(int j=0; j<DIG_LEN-1; j++)
        printf("0");
    }
    printf("%u", x->digits[i]);
    if(i==0) break;
  }
}

// BigInt Operations
BigInt* addn(BigInt* x, BigInt* y){
  BigInt* z = malloc(sizeof(BigInt));
  
  z->cap = x->cap; 
  if(z->cap < y->cap) z->cap = y->cap;
  
  z->cap++;
  z->digits = malloc(
  sizeof(digit_t) * z->cap); 

  size_t sz = x->size;
  if(sz < y->size) sz = y->size;
  
  wide_t sum = 0, carry = 0;
  digit_t xi, yi;
  size_t i;
  for(i=0; i<sz; i++){
    xi= (i < x->size)? x->digits[i]:0;
    yi= (i < y->size)? y->digits[i]:0;
    sum = xi + yi + carry;
    carry = sum / BASE;
    z->digits[i]= sum%BASE;
  }
  if(carry){
    z->digits[i] = carry;
    i++;
  }
  z->size = i;
  return z;
}

BigInt* subn(BigInt* x, BigInt* y){
  if(lt(x, y)){
    printf(ERROR 
    "Negative numbers not allowed\n"
    "Use a custom wrapper to incorporate them\n"
      COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  
  BigInt* z = malloc(sizeof(BigInt));
  
  z->cap = x->cap; 
  
  z->digits = malloc(
  sizeof(digit_t) * z->cap); 

  size_t sz = x->size;
  
  wide_t sub = 0, borrow = 0;
  digit_t xi, yi;
  size_t i;
  for(i=0; i< sz; i++){
    xi = x->digits[i];
    yi = (i < y->size)? y->digits[i]: 0;

    sub = xi + BASE - yi - borrow;
    z->digits[i] = sub % BASE;
    borrow = (sub < BASE);
  }
  z->size = sz;
  return z;
}

bool eq(BigInt* x, BigInt* y){
  if(x->size != y->size) return false;
  for(size_t i=0;
  i<x->size; i++){
    if(x->digits[i] !=
      y->digits[i])
        return false;
  }
  return true;
}

bool lt(BigInt* x, BigInt* y){
  if(x->size < y->size) return true;
  if(x->size > y->size) return false;
  for(size_t i=x->size-1;
  i>=0; i--){
    if(x->digits[i] > y->digits[i])
      return false;
    if(x->digits[i] < y->digits[i])
      return true;
    if(i==0) break;
  }
  return false;
}

bool gt(BigInt* x, BigInt* y){
  if(x->size > y->size) return true;
  if(x->size < y->size) return false;
  for(size_t i=x->size-1;
  i>=0; i--){
    if(x->digits[i] < y->digits[i])
      return false;
    if(x->digits[i] > y->digits[i]){
      return true;}
    if(i==0) break;
  }
  return false;
}

bool geq(BigInt* x, BigInt* y){
  if(x->size > y->size) return true;
  if(x->size < y->size) return false;
  for(size_t i=x->size-1;
  i>=0; i--){
    if(x->digits[i] < y->digits[i])
      return false;
    if(x->digits[i] > y->digits[i])
      return true;
    if(i==0) break;
  }
  return true;
}

bool leq(BigInt* x, BigInt* y){
  if(x->size < y->size) return true;
  if(x->size > y->size) return false;
  for(size_t i=x->size-1;
  i>=0; i--){
    if(x->digits[i] > y->digits[i])
      return false;
    if(x->digits[i] < y->digits[i])
      return true;
    if(i==0) break;
  }
  return true;
}

