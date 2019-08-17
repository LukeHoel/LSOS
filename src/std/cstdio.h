#ifndef STD_CSTDIO
#define STD_CSTDIO
#include "common.h"
#include "cstring.h"

namespace std {

void printf(const char *data, ...);
void putchar(char input);
void puts(char *input);
void sprintf(char *buffer, const char *data, ...);
void sputchar(char *buffer, int i, char input);
void sputs(char *buffer, int i, char *input);
} // namespace std
#endif