#include "head.h"

int parse_signed(const char *s, int base, long long *out)
{
	int neg = 0;

	if (*s == '-' || *s == '+') {
		neg = *s == '-';
		s++;
	}
	if (!*s)
		return 0;

	unsigned long long n = 0, lim = neg ? (unsigned long long)LLONG_MAX + 1 : LLONG_MAX;

	for (; *s; s++) {
		int d = isdigit((unsigned char)*s) ? *s - '0' : toupper((unsigned char)*s) - 'A' + 10;

		if (d < 0 || d >= base || n > (lim - d) / base)
			return 0;
		n = n * base + d;
	}

	if (neg)
		*out = n == (unsigned long long)LLONG_MAX + 1 ? LLONG_MIN : -(long long)n;
	else
		*out = (long long)n;
	return 1;
}

void format_base(long long v, int base, char *out)
{
	const char *d = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char b[128];
	int i = 0;
	unsigned long long n = v < 0 ? 0 - (unsigned long long)v : (unsigned long long)v;

	do {
		b[i++] = d[n % base];
		n /= base;
	} while (n);

	int j = 0;

	if (v < 0)
		out[j++] = '-';
	while (i)
		out[j++] = b[--i];
	out[j] = 0;
}