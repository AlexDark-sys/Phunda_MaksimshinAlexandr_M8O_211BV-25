#include "head.h"

int main(void)
{
	int base;

	if (scanf("%d", &base) != 1 || base < 2 || base > 36) {
		fprintf(stderr, "Base must be [2..36]\n");
		return 1;
	}

	char s[4096];
	long long sum = 0, maxv = 0;
	int have = 0;

	while (scanf("%4095s", s) == 1 && strcmp(s, "Stop") != 0) {
		long long v;

		if (!parse_signed(s, base, &v)) {
			fprintf(stderr, "Invalid/overflowing number: %s\n", s);
			return 1;
		}

		if (!have || ((v == LLONG_MIN) ? 1ULL << 63 : (unsigned long long)llabs(v)) >
			    ((maxv == LLONG_MIN) ? 1ULL << 63 : (unsigned long long)llabs(maxv)))
			maxv = v;

		if ((v > 0 && sum > LLONG_MAX - v) || (v < 0 && sum < LLONG_MIN - v)) {
			fprintf(stderr, "Sum overflow\n");
			return 1;
		}
		sum += v;
		have = 1;
	}

	if (!have) {
		puts("No numbers");
		return 0;
	}

	printf("Maximum absolute value: %lld\n", maxv);
	printf("Sum: %lld\n", sum);

	int bases[] = { 9, 18, 27, 36 };

	for (int i = 0; i < 4; i++) {
		char a[128], b[128];

		format_base(maxv, bases[i], a);
		format_base(sum, bases[i], b);
		printf("base %d: max=%s sum=%s\n", bases[i], a, b);
	}

	return 0;
}

//./program