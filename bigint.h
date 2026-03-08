#ifndef BIG_INT_H
#define BIG_INT_H
#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"
#define BASE 1000000000 // 10^9 BASE
#define DIG_LEN 9
typedef uint32_t digit_t;
typedef uint64_t wide_t; // Used for Operations

// BigInt
// We'll use little endian
typedef struct{
  digit_t* digits;
  size_t size;
  size_t cap;
} BigInt;

// Constructor
BigInt* creatBigInt(digit_t* digits, size_t len);
BigInt* intToBigInt(int x);

// Display on screen
void printBigInt(BigInt* x);

// Operations
BigInt* addn(BigInt* x, BigInt* y);
BigInt* subn(BigInt* x, BigInt* y);
BigInt* mult(BigInt* x, BigInt* y);
BigInt* divn(BigInt* x, BigInt* y);
bool eq(BigInt* x, BigInt* y);
bool lt(BigInt* x, BigInt* y);
bool gt(BigInt* x, BigInt* y);
bool geq(BigInt* x, BigInt* y);
bool leq(BigInt* x, BigInt* y);

// Destructor
void freeBigInt(BigInt** x);
#endif
