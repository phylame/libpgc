#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ELEMENT_TYPE
#define elem_t int
#include <xgc/list.h>

bool w(const elem_t data, void *arg)
{
    printf("%d ", data);
    return false;
}
void pb(bool b)
{
	if (b)
		printf("true ");
	else
		printf("false ");
}

int main()
{
    XList *ls = mklist();
    elem_t ary[10];
    int i;
    for (i = 0; i < 10; ++i) {
        ary[i] = i + 10;
        listadd(ls, ary[i]);
    }
    pb(listins(ls, 6, 99));
    printf("size: %ld\n", listlen(ls));
    listdel(ls, 99);
    printf("size: %ld\n", listlen(ls));
    listpop(ls, 3);
    printf("size: %ld\n", listlen(ls));
    listrv(ls, w, NULL);
    printf("set index:8 to 77\n");
    pb(listset(ls, 8, 77));
    printf("in index: 8 %d\n", listget(ls, 8, 1000));
    printf("\n");
    rmlist(ls);
    return 0;
}
