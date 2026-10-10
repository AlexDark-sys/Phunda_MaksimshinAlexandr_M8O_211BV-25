#include "head.h"

int is_convex(int n, ...)
{
	if (n < 3)
		return 0;

	va_list ap; //va_list - тип для хранения списка аргументов
	double *x = malloc(2 * n * sizeof(double));

	if (!x)
		return 0;

	va_start(ap, n); //va_start - инициализирует список
	for (int i = 0; i < 2 * n; i++)
		x[i] = va_arg(ap, double); //va_arg - достаёт след элемент
	va_end(ap); // va_end - освобождает ресурсы

	int sign = 0, ok = 1;

	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n, k = (i + 2) % n;
		double cross = (x[2 * j] - x[2 * i]) * (x[2 * k + 1] - x[2 * j + 1]) -
		               (x[2 * j + 1] - x[2 * i + 1]) * (x[2 * k] - x[2 * j]);

		if (fabs(cross) > 1e-10) {
			int s = cross > 0 ? 1 : -1;

			if (sign && s != sign)
				ok = 0;
			sign = s;
		}
	}

	free(x);
	return ok && sign != 0;
}

double polynomial(double x, int n, ...)
{
	va_list ap;

	va_start(ap, n);
	double r = va_arg(ap, double);

	for (int i = 1; i <= n; i++)
		r = r * x + va_arg(ap, double);
	va_end(ap);

	return r;
}

int is_kaprekar_one(const char *s, int base)
{
	if (base < 2 || base > 36 || !s || !*s)
		return 0;

	unsigned long long n = 0;

	for (; *s; s++) {
		int d = isdigit((unsigned char)*s) ? *s - '0' : toupper((unsigned char)*s) - 'A' + 10;

		if (d < 0 || d >= base || n > (ULLONG_MAX - d) / base)
			return 0;
		n = n * base + d;
	}

	unsigned long long sq = n * n;

	if (n && sq / n != n)
		return 0;

	unsigned long long p = base;

	while (p <= sq && p <= ULLONG_MAX / base)
		p *= base;

	unsigned long long right = sq % p, left = sq / p;

	return left + right == n;
}

double geomean(int n, ...)
{
	if (n <= 0)
		return NAN;

	va_list ap;

	va_start(ap, n);
	long double sum = 0;

	for (int i = 0; i < n; i++) {
		double x = va_arg(ap, double);

		if (x <= 0 || !isfinite(x)) {
			va_end(ap);
			return NAN; //не число - это макрос из библиотеки math
		}
		sum += log(x);
	}
	va_end(ap);

	return exp((double)(sum / n));
}

double fast_power(double x, int n)
{
	if (n < 0)
		return 1.0 / fast_power(x, -n);
	if (n == 0)
		return 1;

	double h = fast_power(x, n / 2);

	return n % 2 ? x * h * h : h * h;
}

int bisection(double (*f)(double), double a, double b, double e, double *r) //метод бисекции половинного деления
{
	if (!f || !r || !isfinite(a) || !isfinite(b) || e <= 0 || a >= b)
		return 1;

	double fa = f(a), fb = f(b);

	if (fa == 0) {
		*r = a;
		return 0;
	}
	if (fb == 0) {
		*r = b;
		return 0;
	}
	if (fa * fb > 0)
		return 2;

	for (int i = 0; i < 100000 && b - a > e; i++) {
		double m = a + (b - a) / 2, fm = f(m);

		if (fm == 0) {
			a = b = m;
			break;
		}
		if (fa * fm < 0) {
			b = m;
			fb = fm;
		} else {
			a = m;
			fa = fm;
		}
	}

	*r = a + (b - a) / 2;
	return 0;
}

int kaprekar_any(int base, int count, ...)
{
	if (base < 2 || base > 36 || count < 0)
		return 0;

	va_list ap;
	va_start(ap, count);
	int found = 0;

	for (int i = 0; i < count; i++) {
		const char *s = va_arg(ap, const char *);

		if (is_kaprekar_one(s, base))
			found = 1;
	}
	va_end(ap);

	return found;
}