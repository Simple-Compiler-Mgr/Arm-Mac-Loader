#ifndef STDDEF_H
#define STDDEF_H

#include "stdint.h"

#define NULL ((void*)0)

typedef uint64_t size_t;
typedef int64_t ssize_t;
typedef int64_t ptrdiff_t;

#define offsetof(type, member) ((size_t) &((type *)0)->member)

#endif // STDDEF_H