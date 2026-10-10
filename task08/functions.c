#include "head.h"

char *normalize(const char *s)
{
	while (*s == '0' && s[1])
		s++;

	static char b[4096];
	size_t i = 0;

	for (; s[i] && i < 4095; i++)
		b[i] = (char)toupper((unsigned char)s[i]);
	b[i] = 0;
	return b;
}

int parse_number(const char *s, int *base, unsigned long long *v)
{
	if (!s || !*s)
		return 0;

	int max = 0;

	for (const char *p = s; *p; p++) {
		int d = isdigit((unsigned char)*p) ? *p - '0' : toupper((unsigned char)*p) - 'A' + 10;

		if (d < 0 || d >= 36)
			return 0;
		if (d > max)
			max = d;
	}

	*base = max + 1;
	if (*base < 2)
		*base = 2;
	if (*base > 36)
		return 0;

	unsigned long long n = 0;

	for (const char *p = s; *p; p++) {
		int d = isdigit((unsigned char)*p) ? *p - '0' : toupper((unsigned char)*p) - 'A' + 10;

		if (n > (ULLONG_MAX - d) / (*base))
			return 0;
		n = n * (*base) + d;
	}

	*v = n;
	return 1;
}