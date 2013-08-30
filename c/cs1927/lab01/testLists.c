#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"

// insert proper tests here
int main (int argc, const char * argv[]) {
	int start,end;
	printf("input start and end\n");
	scanf("%d %d",&start,&end);

	link list = fromTo (start, end);
	printList (list);
	printf("The sum is %d.\n",sumListItems(list));

	dlink doublelist = doublify(list);
	printDList(doublelist);

	freeList(list);

	freeDList(doublelist);

	return 0;
}
