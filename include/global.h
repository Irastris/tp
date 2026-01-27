#ifndef _global_h_
#define _global_h_

/* #include <cstdint>
#include <cstddef>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;
typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float  f32;
typedef double f64;

typedef volatile f32 vf32;
typedef volatile f64 vf64;

typedef char* Ptr;

typedef int BOOL;

typedef unsigned int uint;

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using uintptr = std::uintptr_t;
using intptr  = std::intptr_t;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL nullptr
#endif */

#define OS_REPORT(...) ((void)0)

#define ALIGN_PREV(X, N) ((X) & ~((N)-1))
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N)-1), N)

#endif
