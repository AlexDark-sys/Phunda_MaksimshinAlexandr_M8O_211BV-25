#include "head.h"

int main(int argc, char **argv)
{
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "Usage: flag input [output] (use -nd/-ni/-ns/-na for explicit output)\n");
		return 1;
	}

	int named = argv[1][1] == 'n';
	char f = named ? argv[1][2] : argv[1][1];

	if ((argv[1][0] != '-' && argv[1][0] != '/') || !strchr("disa", f) || argv[1][named ? 3 : 2]) {
		fprintf(stderr, "Bad flag\n");
		return 1;
	}

	if (named && argc != 4) {
		fprintf(stderr, "Named output required\n");
		return 1;
	}
	if (!named && argc != 3) {
		fprintf(stderr, "Unexpected argument\n");
		return 1;
	}

	char *out = NULL;

	if (named)
		out = strdup(argv[3]);
	else {
		out = malloc(strlen(argv[2]) + 5);
		if (out)
			sprintf(out, "out_%s", argv[2]);
	}
	if (!out) {
		perror("memory");
		return 1;
	}

	int r = transform(argv[2], out, f);

	free(out);
	return r ? 1 : 0;
}

// ./program <флаг> <входной_файл>
//./program -nd input.txt output.txt
//./program -ni input.txt output.txt
//./program -ns input.txt output.txt
//./program -na input.txt output.txt