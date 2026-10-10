#include "head.h"

int is_prime(long long n)
{
	if (n < 2)
		return 0;
	if (n % 2 == 0)
		return n == 2;
	for (long long i = 3; i <= n / i; i += 2)
		if (n % i == 0)
			return 0;
	return 1;
}

void print_hex_digits(unsigned long long n)
{
	char b[32];
	int i = 0;

	if (!n) {
		puts("0");
		return;
	}
	while (n) {
		b[i++] = "0123456789ABCDEF"[n % 16];
		n /= 16;
	}
	while (i) {
		putchar(b[--i]);
		putchar(i ? ' ' : '\n');
	}
}

int factorial(long long n, unsigned long long *r)
{
	*r = 1;
	for (long long i = 2; i <= n; i++) {
		if (*r > ULLONG_MAX / (unsigned long long)i)
			return 0;
		*r *= i;
	}
	return 1;
}