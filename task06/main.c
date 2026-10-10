#include "head.h"

static double f1(double x)
{
	return x * x - 2;
}

static double f2(double x)
{
	return cos(x) - x;
}

int main(void)
{
	printf("convex square: %s\n",
		is_convex(4, 0., 0., 1., 0., 1., 1., 0., 1.) ? "yes" : "no");
	printf("P(2), coeff 1,-3,2 = %.6g\n", polynomial(2., 2, 1., -3., 2.));
	printf("geomean(2,8)=%.6g\n", geomean(2, 2., 8.));
	printf("2^10=%.6g\n", fast_power(2, 10));

	double r;
	int st = bisection(f1, 0, 2, 1e-8, &r);

	printf("bisection x^2-2: status %d, root %.10g\n", st, r);

	st = bisection(f2, 0, 1, 1e-8, &r);
	printf("bisection cos(x)-x: status %d, root %.10g\n", st, r);

	printf("Kaprekar 45 base10: %s\n",
		kaprekar_any(10, 3, "45", "10", "297") ? "yes" : "no");

	return 0;
}

//./program