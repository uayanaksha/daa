#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned comparisons = 0;

static void merge(int array[], int start, int mid, int end){
    int llen = mid - start + 1,
        rlen = end - mid;
    int larr[llen], rarr[rlen];
    int i = 0, j = 0, k = start;
    while (i < llen) {
        larr[i] = array[start + i];
        i++;
    }   i = 0;
    while (j < rlen) {
        rarr[j] = array[mid + 1 + j];
        j++;
    }   j = 0;
    while (i < llen && j < rlen){
        comparisons++;
        if (larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        }   else {
            array[k] = rarr[j];
            j++;
        }   k++;
    }
    while (i < llen) {
        comparisons++;
        array[k] = larr[i];
        i++;
        k++;
    }
    while (j < rlen) {
        comparisons++;
        array[k] = rarr[j];
        j++;
        k++;
    }
}

static void mergesort_r(int array[], int start, int end){
    if(start >= end) return;
    comparisons++;
    int mid = start + (end - start)/2;
    mergesort_r(array, start, mid);
    mergesort_r(array, mid + 1, end);
    merge(array, start, mid, end);
}

unsigned mergesort(int array[], unsigned size){
    mergesort_r(array, 0, size-1);
    return comparisons;
}

void get(int array[], unsigned size){
    if(size < 1) return;
    printf("Array[%u]: [", size);
    for (int i = 0; i < size; i++) {
        printf(" %d,", array[i]);
    }   printf("];\n");
}

int main(void){
    // Get  size of array
    unsigned size;
    printf("Enter size of array: ");
    int err = scanf("%u", &size);
    if(err != 1){
        fprintf(stderr, "Error: Invalid input!\n");
        return 1;
    }
    if(size < 0 || size > 256){
        fprintf(stderr, "Warning: Beyond input range [0~256]!\n");
        return 1;
    }

    // Populate array
    srand(time(0));
    const int low = 250;
    const int high = 750;
    int *array = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        int element = low + rand() % (high - low + 1);
        array[i] = element;
    }   get(array, size);

    // sort
    const int comparison_c = mergesort(array, size);
    get(array, size);
    printf("Total number of comparisons: %u\n", comparison_c);

    // Delete array
    free(array);
    return 0;
}
