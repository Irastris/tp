#ifndef _global_h_
#define _global_h_

/* #include <cstddef>

typedef char* Ptr;

typedef unsigned int uint;

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using uintptr = std::uintptr_t;
using intptr  = std::intptr_t; */

#define ALIGN_PREV(X, N) ((X) & ~((N)-1))
#define ALIGN_NEXT(X, N) ALIGN_PREV(((X) + (N)-1), N)

#endif
