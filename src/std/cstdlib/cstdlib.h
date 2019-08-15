#ifndef CSTDLIB_H
#define CSTDLIB_H
namespace std {
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void *malloc(size_t size);
void free(void *ptr);
} // namespace std
#endif
