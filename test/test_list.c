#include <stdio.h>
#include <xgc/xgc.h>
#include <xgc/list.h>

int main(void)
{
	xnode node = make_node("xxx");
	delete_node(node);
	return 0;
}
