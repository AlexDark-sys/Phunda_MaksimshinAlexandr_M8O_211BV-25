#include "head.h"

int main(int argc, char **argv)
{
	if (argc == 5 && argv[1][0] == '-' && argv[1][2] == '\0' && argv[1][1] == 'r')
		return interleave(argv[2], argv[3], argv[4]);

	if (argc == 4 && argv[1][0] == '-' && argv[1][2] == '\0' && argv[1][1] == 'a')
		return convert(argv[2], argv[3]);

	fprintf(stderr, "Usage: -r file1 file2 output | -a input output\n");
	return 1;
}

//./program -r <файл1> <файл2> <выходной_файл> - ./program -r first.txt second.txt result.txt
//./program -a <входной_файл> <выходной_файл> - ./program -a input.txt result.txt