#ifndef _global_h_
#define _global_h_

/* #include <cstddef>

typedef char* Ptr;

typedef unsigned int uint;

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using uintptr = std::uintptr_t;
using intptr  = std::intptr_t; */

#define ARRAY_SIZE(o) (s32)(sizeof(o) / sizeof(o[0]))
#define ARRAY_SIZEU(o) (sizeof(o) / sizeof(o[0]))

#define ALIGN_PREV(X, N) ((X) & ~((N)-1))
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N)-1), N)

#endif
