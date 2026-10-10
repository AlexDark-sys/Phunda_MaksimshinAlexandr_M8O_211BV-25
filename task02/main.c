#include "head.h"

int main(int argc, char **argv)
{
	char *e;

	errno = 0;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s epsilon\n", argv[0]);
		return 1;
	}

	double eps = strtod(argv[1], &e); //как stroll но для double
	if (errno || *e || !isfinite(eps) || eps <= 0 || eps >= 1) {
		fprintf(stderr, "epsilon must be in (0,1)\n");
		return 1;
	}

	const char *n[] = { "e", "pi", "ln2", "sqrt2", "gamma" };

	for (int i = 0; i < 5; i++) {
		double a, b, c;
		int ok = compute(i, eps, &a, &b, &c);

		printf("%s: series=%.12g equation=%.12g limit=%.12g%s\n",
			n[i], a, b, c, ok ? "" : " (iteration limit reached)");
	}

	return 0;
}

// ./program <epsilon> - ./program 0.001