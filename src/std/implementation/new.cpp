#include "../new.h"

void *operator new(size_t size) { return std::malloc(size); }

void *operator new[](size_t size) { return std::malloc(size); }

#pragma GCC diagnostic ignored "-Wsized-deallocation"
void operator delete(void *p) { std::free(p); }

void operator delete[](void *p) { std::free(p); }