#ifndef CSTDLIB_H
#define CSTDLIB_H
namespace std {
#include "common.h"

void *malloc(size_t size);
void free(void *ptr);
} // namespace std
#endif
