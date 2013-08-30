#include <stdio.h>
#include <stdlib.h>

typedef struct linklist *LS;
struct linklist{
	LS next;
	int item;
};

int main( void ){
	LS table = (LS)malloc(sizeof(LS));
	table->item = 10;
	table->next = NULL;
	printf("%d\n", table->item);

	free(table->next);
	free(table);
	
	return 0;
}
