#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

int is_convex(int n, ...);
double polynomial(double x, int n, ...);
int is_kaprekar_one(const char *s, int base);
int kaprekar_any(int base, int count, ...);
double geomean(int n, ...); //среднее геометрическое
double fast_power(double x, int n); // возведение в степень
int bisection(double (*f)(double), double a, double b, double e, double *r);

#endif