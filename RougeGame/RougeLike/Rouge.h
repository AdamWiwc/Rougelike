#ifndef ROUGE_H
#include <stdint.h>

// NOTE(jesse): Statics can be many things based on where they are placed, so we define these for ease of use
#define internal static
#define local_persist static
#define global_variable static

// NOTE(jesse): If the expression you passed into it isn't true, crash the code by writing into the null pointer
#define Assert(Expression) if (!(Expression)) { *(int*)0 = 0; }

#define ArrayCount(Array) (sizeof(Array)/sizeof(Array[0]))

// NOTE(jesse): Define unsigned char as an Unsigned 8 bit Integer
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
// NOTE(jesse): Optimization: Because booleans must check if a number is not 1 or 0 and change it to 1 if it isn't
// NOTE(jesse): We make a boolean that is just a uint, but for our purposes we just check if one of
// NOTE(jesse): the numbers in the 32 bits is either something or 0. So that way we don't have to make
// NOTE(jesse): The compiler generate code to round down to 1
typedef uint32_t bool32;
// NOTE(jesse): All these use <stdint.h>
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
// NOTE(jesse): Floats are 32 bits wide
typedef float real32;
// NOTE(jesse): Doubles are 64 bits wide
typedef double real64;

#define ROUGE_H
#endif
