#ifndef CSTDLIB_H
#define CSTDLIB_H
#include "common.h"
#include "cstdio.h"
namespace std {
void *malloc(size_t size);
void free(void *ptr);
} // namespace std
#endif
