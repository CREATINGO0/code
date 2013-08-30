#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRSD 50 // threshold

// Function prototypes
void mergeSort(int items[], int low,int numElements);
void mergeSortSC(int items[], int low, int numElements);
void insertionSort2(int items[],int low, int high);
void swap(int x, int y,int items[]);
void printArray(int items[],int low, int high);

//This program sorts ints
// This is where it all happens!
int main(int argc, char *argv[]) {
	int i, numElements;
	int *items;

	// Obtain number of elements and allocate memory to store them
	fprintf(stderr, "Enter number of elements\n");
	scanf("%d", &numElements);
	items = (int *) malloc(numElements * sizeof(int));
	assert(items !=NULL);    

	// Obtain data and store them in array
	fprintf(stderr, "Enter elements to be sorted\n");
	for (i = 0; (i < numElements) && (scanf("%d", &items[i]) != EOF); i++){
		; // Do nothing - it's all done in the for statement!
	}
	numElements = i; // Just in case user entered fewer items

	printf("\nArray before sorting\n");
	printArray(items, 0, numElements - 1);

	// mergeSort(items, 0,numElements-1);
	mergeSortSC(items, 0, numElements-1);

	printf("Array after sorting\n");
	printArray(items, 0, numElements - 1);

	return 0;
}

//An implementation of improved insertion sort - with sentinel and shift
void insertionSortSS(int items[], int low, int high) {
	int i;

	// Move smallest element to the left
	for (i= high; i > low; i--) {
		if (items[i]< items[i - 1]) {
			swap(i, i - 1,items);
		}
	}

	for (i = low+2; i <= high; i++) {
		int j = i;
		int key;
		key = items[i];

		// Shift
		for (j = i; key < items[j - 1]; j--) {
			items[j] = items[j - 1];
		}
		items[j] = key;
	}
}

void merge(int items[], int low, int mid, int high){
	int i, j, k, l;
	int *temp;

	if ((temp  = (int *) malloc((high - low + 1) * sizeof(int))) == NULL){
		fprintf(stderr, "Out of memory - I'm outta here!\n");
		exit(1);
	}

	i = low;
	j = 0;
	k = mid + 1;

	for (; i <= mid && k <= high; j++) {
		if (items[i] <= items[k]) {
			temp[j] = items[i++];
		} else {
			temp[j] = items[k++];
		}
	}

	if (i > mid) {
		for (l = k; l <= high; l++) {
			temp[j++] = items[l];
		}
	} else {
		for (l = i; l <= mid; l++) {
			temp[j++] = items[l];
		}
	}

	// Copy temp array back
	for (k = low; k <= high; k++) {
		items[k] = temp[k - low];
	}

	free(temp); // Release memory
}

//An implementation of standard merge sort
void mergeSort(int items[], int low, int high) {
	int mid;

	if (low < high) {
		mid = (low + high)/2;

		mergeSort(items, low, mid);
		mergeSort(items, mid + 1, high);
		merge(items, low, mid, high);
	}
}

//An implementation of mergeSortSC with sub-file cutoff
void mergeSortSC(int items[], int low, int high) {

	int mid;

	if (low < high) {
		mid = (low + high)/2;

		if( high - low > TRSD ) {
			mergeSortSC(items, low, mid);
			mergeSortSC(items, mid+1, high);
		} else {
			insertionSortSS(items, low, high);
		}
		merge(items, low, mid, high);
	}

}


/* Auxiliary Routines */ 

// Print the contents of an array of integers
// between the indices low and high
void printArray(int items[], int low, int high) {
	int i;

	for (i = low; i <= high; i++){
		printf(" %d", items[i]);
	}
	printf("\n");
}

// Swap two integer values using pass by reference
void swap(int x, int y, int items[]) {
	int temp;
	temp = items[x];
	items[x] = items[y];
	items[y] = temp;
}

