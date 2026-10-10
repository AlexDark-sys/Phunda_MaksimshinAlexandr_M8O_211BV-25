#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

char *normalize(const char *s);
int parse_number(const char *s, int *base, unsigned long long *v);

#endif