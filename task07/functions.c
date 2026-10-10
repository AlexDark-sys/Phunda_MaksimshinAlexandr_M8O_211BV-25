#include "head.h"

static int token(FILE *f, char **s, size_t *cap)
{
	int c;

	do {
		c = fgetc(f);
	} while (c == ' ' || c == '\t' || c == '\n' || c == '\r');

	if (c == EOF)
		return 0;

	size_t n = 0;

	do {
		if (n + 1 >= *cap) {
			size_t nc = *cap ? *cap * 2 : 64;
			char *p = realloc(*s, nc);

			if (!p)
				return -1;
			*s = p;
			*cap = nc;
		}
		(*s)[n++] = c;
		c = fgetc(f);
	} while (c != EOF && c != ' ' && c != '\t' && c != '\n' && c != '\r');

	(*s)[n] = 0;
	return 1;
}

int interleave(const char *a, const char *b, const char *out)
{
	FILE *x = fopen(a, "r"), *y = NULL, *z = NULL;
	char *s = NULL, *t = NULL;
	size_t cs = 0, ct = 0;
	int rx, ry, err = 0;

	if (!x) {
		perror(a);
		return 1;
	}

	y = fopen(b, "r");
	if (!y) {
		perror(b);
		fclose(x);
		return 1;
	}

	z = fopen(out, "w");
	if (!z) {
		perror(out);
		fclose(x);
		fclose(y);
		return 1;
	}

	int first = 1;

	while (1) {
		rx = token(x, &s, &cs);
		ry = token(y, &t, &ct);
		if (rx < 0 || ry < 0) {
			err = 1;
			break;
		}
		if (!rx && !ry)
			break;
		if (rx) {
			if (!first)
				fputc(' ', z);
			fputs(s, z);
			first = 0;
		}
		if (ry) {
			if (!first)
				fputc(' ', z);
			fputs(t, z);
			first = 0;
		}
	}

	fputc('\n', z);
	free(s);
	free(t);

	if (ferror(x) || ferror(y) || ferror(z))
		err = 1;
	if (fclose(x) || fclose(y) || fclose(z))
		err = 1;

	return err;
}

static char *base4(unsigned int n)
{
	char b[32];
	int i = 0;

	do {
		b[i++] = '0' + n % 4;
		n /= 4;
	} while (n);

	char *r = malloc(i + 1);

	if (!r)
		return NULL;

	for (int j = 0; j < i; j++)
		r[j] = b[i - j - 1];
	r[i] = 0;
	return r;
}

int convert(const char *in, const char *out)
{
	FILE *x = fopen(in, "r");

	if (!x) {
		perror(in);
		return 1;
	}

	FILE *y = fopen(out, "w");

	if (!y) {
		perror(out);
		fclose(x);
		return 1;
	}

	char *s = NULL;
	size_t cap = 0;
	int k = 0, err = 0;

	while (token(x, &s, &cap) > 0) {
		k++;
		if (k > 1)
			fputc(' ', y);

		if (k % 10 == 0) {
			for (char *p = s; *p; p++)
				if (*p >= 'A' && *p <= 'Z')
					*p += 32;
			for (char *p = s; *p; p++) {
				char *q = base4((unsigned char)*p);

				if (!q) {
					err = 1;
					break;
				}
				fprintf(y, "%s", q);
				free(q);
			}
		} else if (k % 2 == 0) {
			for (char *p = s; *p; p++)
				fputc((*p >= 'A' && *p <= 'Z') ? *p + 32 : *p, y);
		} else if (k % 5 == 0) {
			for (char *p = s; *p; p++)
				fprintf(y, "%o", (unsigned char)*p);
		} else {
			fputs(s, y);
		}
	}

	fputc('\n', y);
	free(s);

	if (ferror(x) || ferror(y))
		err = 1;
	if (fclose(x) || fclose(y))
		err = 1;

	return err;
}