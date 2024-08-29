#include <time.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned comparisons = 0;

static int partition(int array[], int low, int high){
    int rand_idx = low + rand() % (high - low + 1);
    int pivot = array[rand_idx],
        i = low - 1,
        j = low,
        temp = 0;
    temp = array[rand_idx];
    array[rand_idx] = array[high];
    array[high] = temp;
    while(j < high){
        if (array[j] < pivot){
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }   j++;
        comparisons++;
    }   ++i;
    temp = array[i];
    array[i] = array[high];
    array[high] = temp;
    return i;
}

static void quick_sort_rec(int array[], int start, int end){
    if(end <= start) return;
    int pivot_idx = partition(array, start, end);
    quick_sort_rec(array, start, pivot_idx - 1);
    quick_sort_rec(array, pivot_idx + 1, end);
}

unsigned quick_sort(int array[], int size){
    srand(time(0));
    quick_sort_rec(array, 0, size - 1);
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
    const int comparisons = quick_sort(array, size);
    get(array, size);
    printf("Total number of comparisons: %u\n", comparisons);

    // Delete array
    free(array);
    return 0;
}
