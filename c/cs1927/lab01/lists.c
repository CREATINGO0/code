#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"

void printList (link list) {
	link curr = list;
	while (curr != NULL) {
		printf ("[%d]->", curr->item);
		curr = curr->next;
	}
	printf ("[X]\n");
}

void printDList (dlink dlist) {
	dlink curr = dlist;
	while (curr != NULL) {
		printf ("[%d]->", curr->item);
		curr = curr->next;
	}
	printf ("[X]\n");
}

int sumListItems (link ls) {

	int sum = 0;

	if( ls == NULL)
		return sum;
	else {
		while( ls != NULL ){
			sum += ls->item;
			ls = ls->next;
		}
		return sum;
	}

}

void freeList(link list){
	link ls = list;
	while(list){
		list = list->next;
		free(ls);
		ls = list;

	}
}

void freeDList(dlink list){
	if( list == NULL )
		;

	else{
		dlink ls = list;
		list = list->next;
		while(list){
			list->prev = NULL;
			ls->next = NULL;
			free(ls);
			ls = list;
			list = list->next;
		}
		free(ls);
	}
}

link fromTo (int start, int end) {

	int oncall = start;
	link ls=malloc(sizeof(link)),cur;

	if( start > end )
		return NULL;
	else {

		ls->item = oncall;
		cur = ls;

		while( oncall < end ){
			oncall++;
			cur->next = malloc(sizeof(link));
			cur = cur->next;
			cur->item = oncall;
		}

		return ls;

	}
}

dlink doublify (link list) {

	if( list == NULL )
		return NULL;

	else{
		dlink cur  = malloc(sizeof(dlink));
		dlink head = cur;
		cur->item  = list->item;

		list       = list->next;

		while(list){
			dlink dlist = malloc(sizeof(dlink));
			dlist->item = list->item;
			cur->next   = dlist;
			dlist->prev = cur;
			cur         = dlist;

			list        = list->next;
		}

		return head;
	}
}

