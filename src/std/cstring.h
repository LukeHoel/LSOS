#ifndef CSTRING_H
#define CSTRING_H
#include "common.h"

namespace std {
size_t strlen(const char *str);
int strcmp(const char *str1, const char *str2);
char *strncpy(char *destination, const char *source, size_t num);
} // namespace std
#endif
