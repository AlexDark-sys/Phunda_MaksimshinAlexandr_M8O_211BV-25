#include "head.h"

double series(int id, double ep)
{
	double s = 0, t = 1;
	int n = 0;

	for (; n < 100000; n++) {
		if (id == 0)
			t = (n == 0 ? 1 : t * 1.0 / n);
		else if (id == 1)
			t = (n == 0 ? 1 : t * (-1.0) / (2 * n * (2 * n - 1)));
		else if (id == 2)
			t = (n == 0 ? 1 : t * 27.0 * (n + 1) * (n + 1) * (n + 1) / ((3 * n + 1) * (3 * n + 2) * (3 * n + 3)));
		else
			t = (n == 0 ? 0 : t * (-1.0) * (2 * n - 1) / (2 * n));
		if (id == 3 && n == 0)
			continue;
		s += t;
		if (n > 2 && fabs(t) < ep)
			break;
	}
	return s;
}

static double fun(int id, double x)
{
	switch (id) {
	case 0:
		return x == 0 ? 1 : log1p(x) / x;
	case 1:
		return exp(-x * x / 2);
	case 2:
		return -log(1 - x);
	default:
		return x == 0 ? 0 : pow(x, x);
	}
}

double integral(int id, double ep)
{
	int n = 1000;
	double old = 0, cur = 0;

	for (int pass = 0; pass < 12; pass++) {
		n *= 2;
		double h = 1.0 / n, s = fun(id, 0) + fun(id, 1);

		for (int i = 1; i < n; i++)
			s += (i % 2 ? 4 : 2) * fun(id, i * h);
		cur = s * h / 3;
		if (fabs(cur - old) < ep)
			break;
		old = cur;
	}
	return cur;
}