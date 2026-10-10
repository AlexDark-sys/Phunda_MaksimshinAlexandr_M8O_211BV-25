#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int parse_signed(const char *s, int base, long long *out);
void format_base(long long v, int base, char *out);

#endif