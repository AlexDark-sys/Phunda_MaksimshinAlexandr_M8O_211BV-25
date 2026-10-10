#include "head.h"

int main(int argc, char **argv)
{
	char *e;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s epsilon\n", argv[0]);
		return 1;
	}

	errno = 0;
	double ep = strtod(argv[1], &e);

	if (errno || *e || !isfinite(ep) || ep <= 0 || ep >= 1)
		return 1;

	for (int i = 0; i < 4; i++)
		printf("series %c = %.12g\n", 'a' + i, series(i, ep));

	for (int i = 0; i < 4; i++)
		printf("integral %c = %.12g\n", 'a' + i, integral(i, ep));

	return 0;
}

// ./program <epsilon> - ./program 0.001