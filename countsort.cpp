#include <time.h>
#include <stdio.h>
#include <stdlib.h>

unsigned counting_sort(int array[], int size){
    int min = 2147483647, max = -2147483648;
    unsigned comparisons = 0;
    for(int i = 0; i < size; i++){
        if(array[i] < min) min = array[i];
        if(array[i] > max) max = array[i];
        comparisons+=2;
    }
    int newSize = max - min + 1;
    int *ctr = (int*) (int*)calloc(newSize, sizeof(int));
    for(int i = 0; i < size; i++){
        ctr[array[i] - min]++;
    }
    int idx = 0;
    for(int i = 0; i < newSize; i++){
        while(ctr[i] > 0){
            array[idx] = i + min;
            ctr[i]--;
            idx++;
            comparisons++;
        }   comparisons++;
    }   free(ctr);
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
    int *array = (int*)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        int element = low + rand() % (high - low + 1);
        array[i] = element;
    }   get(array, size);

    // sort
    const int comparisons = counting_sort(array, size);
    get(array, size);
    printf("Total number of comparisons: %u\n", comparisons);

    // Delete array
    free(array);
    return 0;
}
