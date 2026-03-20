#include "bigint.h"
#include "assert.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
// Display colors for errors and warnings
#define ERROR "\x1b[31m"
#define WARNING "\033[33m"
#define COLOR_RESET "\x1b[0m"

// helper function
void throwError(const char *err_msg) {
  printf(ERROR "%s\n" COLOR_RESET, err_msg);
  exit(EXIT_FAILURE);
}

void throwWarning(const char *warn_msg) {
  printf(WARNING "%s\n" COLOR_RESET, warn_msg);
}

// BigInt Constructors
BigInt *creatBigInt(digit_t *digits, size_t len) {
  BigInt *out = malloc(sizeof(BigInt));
  if (out == NULL)
    throwError("Unable to allocate space for BigInt - creatBigInt\n");

  out->size = len;
  out->cap = pow(2, ceil(log2(len)));

  if (len == out->cap) {
    out->digits = digits;
    return out;
  }
  out->digits = realloc(digits, sizeof(digit_t) * out->cap);
  if (out->digits == NULL)
    throwError("Unable to re-allocate space for BigInt - creatBigInt");
  return out;
}

BigInt *intToBigInt(int x) {
  BigInt *out = malloc(sizeof(BigInt));
  if (out == NULL)
    throwError("Unable to allocate space for BigInt - intToBigInt");
  if (x == 0) {
    out->size = 1;
    out->cap = 2;
    out->digits = malloc(sizeof(digit_t) * out->cap);
    out->digits[0] = 0;
    return out;
  }
  out->size = floor(log10(x) / log10(BASE)) + 1;
  out->cap = pow(2, ceil(log2(out->size)));
  out->digits = malloc(sizeof(digit_t) * out->cap);

  int tmp = x, i = 0;
  while (tmp) {
    out->digits[i] = tmp % BASE;
    tmp = tmp / BASE;
    i++;
  }

  while (i < out->size) {
    out->digits[i] = 0;
    i++;
  }
  return out;
}

BigInt *copy(BigInt *x) {
  BigInt *out = malloc(sizeof(BigInt));
  out->cap = x->cap;
  out->size = x->size;
  out->digits = malloc(sizeof(digit_t) * out->cap);
  for (size_t i = 0; i < out->size; i++)
    out->digits[i] = x->digits[i];
  return out;
}

// BigInt Destructors
void freeBigInt(BigInt **x) {
  if (x && *x) {
    free((*x)->digits);
    free(*x);
    *x = NULL;
    return;
  }
  throwWarning("Trying to free NULL pointer - freeBigInt");
}

// Displaying BigInt (big endian)
void printBigInt(BigInt *x) {
  for (size_t i = x->size - 1; i >= 0; i--) {
    if (i != x->size - 1 && x->digits[i]) {
      int lz = floor(log10(x->digits[i])) + 1;
      lz = DIG_LEN - lz;
      for (int j = 0; j < lz; j++)
        printf("0");
    } else if (x->digits[i] == 0 && i != x->size - 1) {
      for (int j = 0; j < DIG_LEN - 1; j++)
        printf("0");
    }
    printf("%u", x->digits[i]);
    if (i == 0)
      break;
  }
}

// BigInt Operations
BigInt *addn(BigInt *x, BigInt *y) {
  BigInt *z = malloc(sizeof(BigInt));

  z->cap = x->cap;
  if (z->cap < y->cap)
    z->cap = y->cap;

  z->cap++;
  z->digits = malloc(sizeof(digit_t) * z->cap);

  size_t sz = x->size;
  if (sz < y->size)
    sz = y->size;

  wide_t sum = 0, carry = 0;
  digit_t xi, yi;
  size_t i;
  for (i = 0; i < sz; i++) {
    xi = (i < x->size) ? x->digits[i] : 0;
    yi = (i < y->size) ? y->digits[i] : 0;
    sum = xi + yi + carry;
    carry = sum / BASE;
    z->digits[i] = sum % BASE;
  }
  if (carry) {
    z->digits[i] = carry;
    i++;
  }
  z->size = i;
  return z;
}

BigInt *subn(BigInt *x, BigInt *y) {
  if (lt(x, y)) {
    printf(WARNING "Negative numbers not implemented\n"
                   "Use a custom wrapper to incorporate them\n" COLOR_RESET);
    //  exit(EXIT_FAILURE);
  }

  BigInt *z = malloc(sizeof(BigInt));

  z->cap = x->cap;

  z->digits = malloc(sizeof(digit_t) * z->cap);

  size_t sz = x->size;

  wide_t sub = 0, borrow = 0;
  digit_t xi, yi;
  size_t i;
  for (i = 0; i < sz; i++) {
    xi = x->digits[i];
    yi = (i < y->size) ? y->digits[i] : 0;

    sub = xi + BASE - yi - borrow;
    z->digits[i] = sub % BASE;
    borrow = (sub < BASE);
  }
  z->size = sz;
  return z;
}

BigInt *mult(BigInt *x, BigInt *y) {
  BigInt *z = malloc(sizeof(BigInt));
  z->cap = x->cap + y->cap;

  z->digits = malloc(sizeof(digit_t) * z->cap);
  z->size = 0;
  for (size_t i = 0; i < z->cap; i++)
    z->digits[i] = 0;

  wide_t tmp, carry = 0, xi, yj;
  size_t i, j;
  for (i = 0; i < x->size; i++) {
    carry = 0;
    xi = x->digits[i];

    for (j = 0; j < y->size; j++) {
      yj = y->digits[j];

      tmp = z->digits[i + j] + xi * yj + carry;
      z->digits[i + j] = tmp % BASE;
      carry = tmp / BASE;
    }
    z->digits[i + y->size] += carry;
    z->size = (carry ? i + y->size + 1 : i + y->size);
  }

  return z;
}

BigInt *shift_left(BigInt *x, size_t k) {
  if (x == NULL) {
    printf(ERROR
           "Null pointer passed as an argument to left shift" COLOR_RESET);
    exit(EXIT_FAILURE);
  }
  BigInt *z = malloc(sizeof(BigInt));
  assert(z && " unable to allocate");
  z->cap = pow(2, ceil(log2(x->size + k)));
  z->size = k + x->size;
  z->digits = malloc(sizeof(digit_t) * z->cap);

  for (size_t i = 0; i < k; i++) {
    z->digits[i] = 0;
  }
  for (size_t i = 0; i < x->size; i++) {
    z->digits[i + k] = x->digits[i];
  }
  return z;
}

BigInt *mult_digit(BigInt *x, digit_t y) {
  wide_t tmp;
  digit_t carry = 0;
  BigInt *z = malloc(sizeof(BigInt));
  z->cap = x->cap + 1;
  z->size = x->size;
  z->digits = malloc(sizeof(digit_t) * z->cap);
  for (size_t i = 0; i < x->size; i++) {
    tmp = (wide_t)y * x->digits[i] + carry;
    z->digits[i] = tmp % BASE;
    if (tmp >= BASE)
      carry = tmp / BASE;
    else
      carry = 0;
  }
  if (carry) {
    z->digits[z->size] = carry;
    z->size++;
  }
  return z;
}

BigInt *divn(BigInt *x, BigInt *y) {
  BigInt *zero = intToBigInt(0);
  assert(gt(y, zero));

  if (lt(x, y)) {
    return zero;
  }
  BigInt *z = malloc(sizeof(BigInt));
  z->cap = x->size - y->size + 1;
  z->digits = calloc(z->cap, sizeof(digit_t));
  z->size = z->cap;
  BigInt *r = copy(x);
  for (ssize_t i = (ssize_t)(x->size - y->size); i >= 0; i--) {
    wide_t numerator =
        (wide_t)r->digits[i + y->size] * BASE + r->digits[i + y->size - 1];
    wide_t qhat = numerator / y->digits[y->size - 1];
    if (qhat >= BASE)
      qhat = BASE - 1;
    // Multiply y * qhat and subtract from r shifted by i
    BigInt *t = mult_digit(y, (digit_t)qhat); // y * qhat
    BigInt *t_shift = shift_left(t, i);       // shift by i digits
    // Fix overestimate
    while (gt(t_shift, r)) {
      qhat--;
      freeBigInt(&t_shift);
      freeBigInt(&t);

      t = mult_digit(y, (digit_t)qhat);
      t_shift = shift_left(t, i);
    }

    r = subn(r, t_shift); // r = r - t_shift
    z->digits[i] = (digit_t)qhat;

    freeBigInt(&t);
    freeBigInt(&t_shift);
  }

  while (z->size > 1 && z->digits[z->size - 1] == 0) {
    z->size--;
  }

  return z;
}

bool eq(BigInt *x, BigInt *y) {
  if (x->size != y->size)
    return false;
  for (size_t i = 0; i < x->size; i++) {
    if (x->digits[i] != y->digits[i])
      return false;
  }
  return true;
}

bool lt(BigInt *x, BigInt *y) {
  if (x->size < y->size)
    return true;
  if (x->size > y->size)
    return false;
  for (size_t i = x->size - 1; i >= 0; i--) {
    if (x->digits[i] > y->digits[i])
      return false;
    if (x->digits[i] < y->digits[i])
      return true;
    if (i == 0)
      break;
  }
  return false;
}

bool gt(BigInt *x, BigInt *y) {
  if (x->size > y->size)
    return true;
  if (x->size < y->size)
    return false;
  for (size_t i = x->size - 1; i >= 0; i--) {
    if (x->digits[i] < y->digits[i])
      return false;
    if (x->digits[i] > y->digits[i]) {
      return true;
    }
    if (i == 0)
      break;
  }
  return false;
}

bool geq(BigInt *x, BigInt *y) {
  if (x->size > y->size)
    return true;
  if (x->size < y->size)
    return false;
  for (size_t i = x->size - 1; i >= 0; i--) {
    if (x->digits[i] < y->digits[i])
      return false;
    if (x->digits[i] > y->digits[i])
      return true;
    if (i == 0)
      break;
  }
  return true;
}

bool leq(BigInt *x, BigInt *y) {
  if (x->size < y->size)
    return true;
  if (x->size > y->size)
    return false;
  for (size_t i = x->size - 1; i >= 0; i--) {
    if (x->digits[i] > y->digits[i])
      return false;
    if (x->digits[i] < y->digits[i])
      return true;
    if (i == 0)
      break;
  }
  return true;
}
