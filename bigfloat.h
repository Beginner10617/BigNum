#ifndef "BIG_FLOAT_H"
#define "BIG_FLOAT_H"
#include "bigint.h"

// BigFloat
typedef struct{
  BigInt* mantissa;
  digit_t exponent; // exponent of BASE - defined in bigint.h
} BigFloat;

// Constructor
BigFloat* creatBigFloat(digit_t* digits, size_t len, digit_t exponent);

// Operations
BigFloat* add(BigFloat* x, BigFloat* y);
BigFloat* sub(BigFloat* x, BigFloat* y);
BigFloat* mul(BigFloat* x, BigFloat* y);
BigFloat* div(BigFloat* x, BigFloat* y);

// Destructor
void freeBigFloat(BigFloat* x);
#endif
