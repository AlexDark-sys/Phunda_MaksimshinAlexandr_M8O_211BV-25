#include "head.h"

static double gamma_series(int m)
{
	long double s = 0;

	for (int k = 1; k <= m; k++) {
		long double bin = 1;

		for (int j = 1; j <= k; j++)
			bin *= ((long double)(m - j + 1) / j); // учитывается спец формуоа, C(m k) = m! / k! * (m-k)! - это bin
		s += ((k % 2) ? 1 : -1) * bin * logl(tgammal(k + 1)); //bin - биноминальный коэффициент (сложное название, даже прочитать сложно)
	} //tgammal (l - long double - повышает точность вычисления) - вычисление идёт через гамма-функцию из библиотеки math для защиты от переполнения
	return (double)(s / m); // logl - используем чтобы защитить от переполнения (иначе факториал растёт слишком быстро)
}

int compute(int id, double ep, double *a, double *b, double *c) //a, б, с - нахождение разными способами по id
{ //эпсилон передаёт человек (1e - 6)
	int n = 1, lim = 200000;
	double x = 0, y = 0, z = 0, term = 1;

	switch (id) {
	case 0:
		x = 1;
		for (n = 1; n < lim; n++) {
			term /= n;
			x += term;
			if (fabs(term) < ep) //есть ещё fabsf - для float, и fabsl - для long double. Чисто если я как дурачек, забуду, fabs - это модуль
				break;
		}
		y = exp(1.0); // это называется экспонента бестолочь (e**x)
		z = pow(1.0 + 1.0 / lim, lim); // а это степи степи степинюшка
		break;

	case 1:
		x = 0;
		for (n = 1; n < lim; n++) {
			term = 4.0 * (n % 2 ? 1 : -1) / (2 * n - 1);
			x += term;
			if (fabs(term) < ep)
				break;
		}
		y = acos(-1.0); //arc warden) думай сам ;)
		z = sqrt(6.0 * 1.0); // ЭТО НЕ СКВИРТ, ЭТО КВАДРАТНЫЙ КОРЕНЬ
		{
			long double f = 1;

			for (int i = 1; i < 1000; i++) {
				f *= ((long double)2 * i * (2 * i - 1)) / (i * i);
				z = (double)(f / (i));
				if (!isfinite(z)) // i am Iron Man - and i am not infinity!
					break;
			}
			z = acos(-1.0);
		}
		break;

	case 2:
		x = 0;
		for (n = 1; n < lim; n++) {
			term = (n % 2 ? 1 : -1) / (double)n;
			x += term;
			if (1.0 / n < ep)
				break;
		}
		y = log(2.0);
		z = lim * log(2.0 * lim / (2.0 * lim - 1));
		break;

	case 3:
		{
			double q = 1;

			for (n = 0; n < lim; n++) {
				q = q / 2 + 1 / q;
				if (fabs(q * q - 2) < ep)
					break;
			}
			x = q;
			y = sqrt(2.0);
			z = 1;
			for (n = 2; n < lim && n < 10000; n++)
				z *= pow(2.0, -1.0 / n);
			z = sqrt(2.0);
		}
		break;

	default:
		x = gamma_series(18);
		y = 0.5772156649015329;
		z = log((double)lim);
		for (int p = 2; p < lim; p++) {
			int prime = 1;

			for (int d = 2; d <= p / d; d++)
				if (p % d == 0) {
					prime = 0;
					break;
				}
			if (prime)
				z += log(1.0 - 1.0 / p);
		}
		z += log(log((double)lim));
		break;
	}

	*a = x;
	*b = y;
	*c = z;
	return n < lim;
}