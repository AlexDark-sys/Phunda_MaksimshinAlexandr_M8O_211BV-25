#include "head.h"

void swap_min_max(int *a, size_t n, int *mn, int *mx)
{
	if (!a || !n)
		return;

	size_t imin = 0, imax = 0;

	for (size_t i = 1; i < n; i++) {
		if (a[i] < a[imin])
			imin = i;
		if (a[i] > a[imax])
			imax = i;
	}

	*mn = a[imin];
	*mx = a[imax];

	int t = a[imin];

	a[imin] = a[imax];
	a[imax] = t;
}