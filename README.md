# BigInt Library in C
This project is a basic implementation of arbitrary-precision integer arithmetic (BigInt) in C. It supports creation, manipulation, and arithmetic operations on integers larger than the native data types.

---
## Features

### Core Functionality
- Create BigInt from digit arrays or integers
- Copy and free BigInt structures
- Print BigInt values

### Arithmetic Operations
- Addition
- Subtraction
- Multiplication
- Division
- Modulo
- Combined division and remainder (divmod)

### Comparison Operations
- Equal to
- Less than / Greater than
- Less than or equal to / Greater than or equal to

### Helper Functions
- Multiply by a single digit
- Left shift (digit-wise)

### File Structure
- `bigint.c` / `bigint.h` – Implementation and declarations of BigInt structure and operations
- `main.c` – Example usage (includes computation of π using BigInt)

---
## Usage
Compile the project using:
```
gcc main.c bigint.c -o bigint
```

Run the executable:
```
./bigint
```

---
## Design Notes
- Numbers are stored as arrays of digits
- Memory is dynamically allocated for all BigInt objects
- Operations return new BigInt instances rather than modifying inputs

---
## Limitations
- Performance is currently limited due to frequent memory allocation and deallocation
- Division and multiplication use basic (schoolbook) algorithms
- No optimization for large-scale computations yet

---
## Future Improvements
- Optimize memory usage (reduce allocations, introduce in-place computations)
- Implement faster algorithms (Karatsuba multiplication, long division optimizations)
- Add support for negative numbers
- Improve API ergonomics (in-place operations)

---
## Status
This project is currently paused due to performance issues. It may be revisited later with a focus on optimization and improved design.
