#include "head.h"

int transform(const char *in, const char *out, char op)
{
	FILE *a = fopen(in, "r");

	if (!a) {
		perror(in);
		return 1;
	}

	FILE *b = fopen(out, "w");

	if (!b) {
		perror(out);
		fclose(a);
		return 1;
	}

	char *line = NULL;
	size_t cap = 0;
	ssize_t n;
	int err = 0;

	while ((n = getline(&line, &cap, a)) != -1) {
		if (op == 'd') {
			for (ssize_t i = 0; i < n; i++)
				if (line[i] < '0' || line[i] > '9')
					fputc(line[i], b);
		} else if (op == 'i' || op == 's') {
			int count = 0;

			for (ssize_t i = 0; i < n; i++) {
				unsigned char c = line[i];

				if (op == 'i'
					? ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
					: (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
					     (c >= '0' && c <= '9') || c == ' ' ||
					     c == '\n' || c == '\t' || c == '\r')))
					count++;
			}
			fprintf(b, "%d\n", count);
		} else {
			for (ssize_t i = 0; i < n; i++) {
				unsigned char c = line[i];

				if ((c >= '0' && c <= '9') || c == '\n' || c == '\r')
					fputc(c, b);
				else
					fprintf(b, "%X", c);
			}
		}
	}

	if (ferror(a) || ferror(b))
		err = 1;

	free(line);

	if (fclose(a))
		err = 1;
	if (fclose(b))
		err = 1;

	if (err)
		fprintf(stderr, "File operation error\n");

	return err;
}