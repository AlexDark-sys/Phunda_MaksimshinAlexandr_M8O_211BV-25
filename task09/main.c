#include "head.h"

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s a b\n", argv[0]);
		return 1;
	}

	char *e;
	long a = strtol(argv[1], &e, 10);

	if (*e)
		return 1;

	long b = strtol(argv[2], &e, 10);

	if (*e || a > b)
		return 1;

	int x[100];

	srand((unsigned)time(NULL));
	for (int i = 0; i < 100; i++)
		x[i] = (int)(a + (long long)rand() % (b - a + 1));

	int mn, mx;

	swap_min_max(x, 100, &mn, &mx);
	printf("array1 min=%d max=%d (swapped)\n", mn, mx);

	size_t na = 10 + rand() % 9991, nb = 10 + rand() % 9991;
	int *A = malloc(na * sizeof(int)), *B = malloc(nb * sizeof(int)), *C = malloc(na * sizeof(int));

	if (!A || !B || !C) {
		free(A);
		free(B);
		free(C);
		fprintf(stderr, "Allocation failed\n");
		return 1;
	}

	for (size_t i = 0; i < na; i++)
		A[i] = rand() % 2001 - 1000;
	for (size_t i = 0; i < nb; i++)
		B[i] = rand() % 2001 - 1000;

	for (size_t i = 0; i < na; i++) {
		int best = B[0];
		long long dist = llabs((long long)A[i] - best);

		for (size_t j = 1; j < nb; j++) {
			long long d = llabs((long long)A[i] - B[j]);

			if (d < dist) {
				dist = d;
				best = B[j];
			}
		}
		C[i] = A[i] + best;
	}

	printf("dynamic arrays sizes A=%zu B=%zu C=%zu; C[0]=%d\n", na, nb, na, C[0]);

	free(A);
	free(B);
	free(C);
	return 0;
}

// ./program <a> <b> - ./program 1 100