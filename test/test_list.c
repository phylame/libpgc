#include <stdio.h>
#include <stdlib.h>
#define ELEMENT_TYPE
typedef double elem_t;
#include <xgc/xgc.h>
#include <xgc/list.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#define cnt 1000000

int main(void)
{
	double ary[cnt];
	int i;
	struct sysinfo si;
	sysinfo(&si);
	printf("free: %ld\n", si.freeram);
	XList *ls = mklist();
	for (i = 0; i < cnt; ++i) {
		ary[i] = rand();
		listadd(ls, ary[i]);
	}
	printf("size of list: %ld\n", listlen(ls));
	rmlist(ls);
	sysinfo(&si);
	printf("free: %ld\n", si.freeram);
	return 0;
}
