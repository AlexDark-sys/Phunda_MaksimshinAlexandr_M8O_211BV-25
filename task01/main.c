#include "head.h"

int main(int argc, char **argv)
{
	long long x;
	char *e;

	if (argc != 3 || (argv[2][0] != '-' && argv[2][0] != '/') || argv[2][2]) {
		fprintf(stderr, "Usage: %s x -h|-p|-s|-e|-a|-f\n", argv[0]);
		return 1;
	}
	
	errno = 0;
	x = strtoll(argv[1], &e, 10);
	if (errno || *e || x < 0) {
		fprintf(stderr, "x must be a nonnegative integer\n");
		return 1;
	}

	switch (argv[2][1]) {
	case 'h':
		if (x == 0) {
			puts("No positive multiples of 0");
			break;
		}
		{
			int found = 0;

			for (int i = 1; i <= 100; i++)
				if (i % x == 0) {
					printf("%d ", i);
					found = 1;
				}
			if (!found)
				puts("No multiples in [1,100]");
			else
				puts("");
		}
		break;

	case 'p':
		printf("%lld is %s\n", x,
			is_prime(x) ? "prime" : (x > 1 ? "composite" : "neither prime nor composite"));
		break;

	case 's':
		print_hex_digits((unsigned long long)x);
		break;

	case 'e':
		if (x > 10) {
			fprintf(stderr, "For -e x must be <= 10\n");
			return 1;
		}
		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= x; j++) {
				long long v = 1;

				for (int k = 0; k < j; k++) {
					if (v > LLONG_MAX / i) {
						puts("overflow");
						return 1;
					}
					v *= i;
				}
				printf("%lld^%d=%lld\n", (long long)i, j, v);
			}
		}
		break;

	case 'a':
		if (x > 6074000999LL) {
			fprintf(stderr, "sum overflow\n");
			return 1;
		}
		printf("%lld\n", x * (x + 1) / 2);
		break;

	case 'f':
		{
			unsigned long long r;

			if (!factorial(x, &r)) {
				fprintf(stderr, "factorial overflow or x too large\n");
				return 1;
			}
			printf("%llu\n", r);
		}
		break;

	default:
		fprintf(stderr, "Unknown flag\n");
		return 1;
	}

	return 0;
}

// коммы для вывода: ./program <наше число> <флаг>