#include "head.h"

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s input output\n", argv[0]);
		return 1;
	}

	FILE *in = fopen(argv[1], "r");

	if (!in) {
		perror(argv[1]);
		return 1;
	}

	FILE *out = fopen(argv[2], "w");

	if (!out) {
		perror(argv[2]);
		fclose(in);
		return 1;
	}

	char s[4096];
	int err = 0;

	while (fscanf(in, "%4095s", s) == 1) {
		int base;
		unsigned long long v;

		if (!parse_number(s, &base, &v)) {
			fprintf(stderr, "Invalid/overflowing token: %s\n", s);
			err = 1;
			continue;
		}
		fprintf(out, "%s %d %llu\n", normalize(s), base, v);
	}

	if (ferror(in) || ferror(out))
		err = 1;

	fclose(in);
	fclose(out);
	return err;
}

//./program <входной_файл> <выходной_файл> - ./program numbers.txt result.txt