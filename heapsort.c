#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned comparisons = 0;

void heapify(int array[], int size, int i){
    int largest = i,
        left = 2 * i + 1,
        right = 2 * i + 2,
        temp = 0;
    if(left < size && array[left] > array[largest]){
        largest = left;
        comparisons++;
    }
    if(right < size && array[right] > array[largest]){
        largest = right;
        comparisons++;
    }
    if(largest != i){
        temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        heapify(array, size, largest);
    }
}

unsigned heap_sort(int array[], int size){
    int i = size / 2 - 1,
        temp = 0;
    for(; i >= 0; --i){
        heapify(array, size, i);
    }
    for(i = size - 1;i > 0; --i){
        temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);
    }   return comparisons;
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
    const int comparisons = heap_sort(array, size);
    get(array, size);
    printf("Total number of comparisons: %u\n", comparisons);

    // Delete array
    free(array);
    return 0;
}
