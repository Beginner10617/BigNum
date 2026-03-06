#ifndef "BIG_INT_H"
#define "BIG_INT_H"
#include "stdint.h"

#define BASE 1000000000 // 10^9 BASE
typedef uint32_t digit_t
typedef uint64_t wide_t // Used for Operations

// BigInt
typedef struct{
  digit_t* digits;
  size_t size;
  size_t cap;
} BigInt;

// Constructor
BigInt* creatBigInt(digit_t* digits, size_t len);

// Operations
BigInt* add(BigInt* x, BigInt* y);
BigInt* sub(BigInt* x, BigInt* y);
BigInt* mul(BigInt* x, BigInt* y);
BigInt* div(BigInt* x, BigInt* y);

// Destructor
void freeBigInt(BigInt* x);
#endif
