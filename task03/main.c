#include "head.h"

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: -m a b | -q eps a b c | -t eps a b c\n");
		return 1;
	}

	char f = argv[1][1];

	if ((argv[1][0] != '-' && argv[1][0] != '/') || argv[1][2])
		return 1;

	char *e;
	double v[4];
	int need = f == 'm' ? 2 : 4;

	if ((f != 'm' && f != 'q' && f != 't') || argc != need + 2) {
		fprintf(stderr, "Wrong flag/argument count\n");
		return 1;
	}

	for (int i = 0; i < need; i++) {
		errno = 0;
		v[i] = strtod(argv[i + 2], &e);
		if (errno || *e || !isfinite(v[i])) {
			fprintf(stderr, "Invalid number\n");
			return 1;
		}
	}

	if (f == 'm') {
		long long a = (long long)v[0], b = (long long)v[1];

		if (v[0] != a || v[1] != b || !a || !b) {
			fprintf(stderr, "Need nonzero integers\n");
			return 1;
		}
		printf("%s\n", a % b == 0 ? "multiple" : "not multiple");
	} else if (v[0] <= 0) {
		fprintf(stderr, "epsilon must be positive\n");
		return 1;
	} else if (f == 't') {
		printf("%s\n", triangle(v[1], v[2], v[3], v[0])
			? "right triangle possible" : "not a right triangle");
	} else {
		int perm[6][3] = {
			{ 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 },
			{ 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 }
		};

		for (int i = 0; i < 6; i++) {
			int dup = 0;

			for (int j = 0; j < i; j++)
				if (v[1 + perm[i][0]] == v[1 + perm[j][0]] &&
				    v[1 + perm[i][1]] == v[1 + perm[j][1]] &&
				    v[1 + perm[i][2]] == v[1 + perm[j][2]])
					dup = 1;
			if (!dup)
				solve(v[1 + perm[i][0]], v[1 + perm[i][1]],
				      v[1 + perm[i][2]], v[0]);
		}
	}

	return 0;
}

// ./program -m <a> <b> - ./program -m 12 3
// ./program -q <epsilon> <a> <b> <c> - ./program -q 0.001 1 -3 2
//./program -t <epsilon> <a> <b> <c> - ./program -t 0.001 3 4 5