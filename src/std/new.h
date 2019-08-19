#ifndef NEW_H
#define NEW_H
#include "common.h"
#include "cstdlib.h"
void *operator new(size_t size);

void *operator new[](size_t size);

void operator delete(void *p);

void operator delete[](void *p);
#endif