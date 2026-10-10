#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int is_prime(long long n);
void print_hex_digits(unsigned long long n);
int factorial(long long n, unsigned long long *r);

#endif