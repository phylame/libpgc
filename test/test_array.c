#include <stdio.h>
#include <stdbool.h>
#define ELEMENT_TYPE
#define elem_t int
#include <xgc/array.h>

void pb(bool b)
{
	printf(b ? "true, " : "false, ");
}

bool w(elem_t v, void *arg)
{
	printf("%d ", v);
	return false;
}

void pa1(XArray *ary)
{
	printf("size=%ld, capacity=%ld: ", arylen(ary), arycap(ary));
	arytrv(ary, w, NULL);
	printf("\n");
}

void pa2(XArray *ary)
{
	elem_t *iter;
	printf("size=%ld, capacity=%ld: ", arylen(ary), arycap(ary));
	for (iter = arybeg(ary); iter != aryend(ary); iter = arynext(ary, iter))
		printf("%d ", *iter);
	printf("\n");
}


int main(void)
{
	int i;
	XArray *ary1 = mkary(), *ary = mkary();
	elem_t abc;
	for (i = 0; i < 5; ++i)
		aryadd(ary1, i + 15);	// append
	for (i = 0; i < 10; ++i)
		aryadd(ary, i);
	aryins(ary, 5, 888);		// insert
	aryext(ary, ary1);		// extend
	pa1(ary);
	arydel(ary, 888);		// delete by value
	arypop(ary, 9, &abc);		// delete by index
	aryset(ary, 3, 1992);
	pa2(ary);
	rmary(ary);			// free array
	rmary(ary1);
	return 0;
}
