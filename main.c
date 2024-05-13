#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

//Сортировка перемешиванием

void sheker_sort(int * vec, int size){
    int start_index = 0, end_index = size -1, flag = 1;
    int tmp;
    while ((start_index < end_index) && flag){
        flag = 0;
        for (int i = start_index; i < end_index; i++){
            if (vec[i] > vec[i+1]){
                tmp = vec[i];
                vec[i] = vec[i+1];
                vec[i+1] = tmp;
                flag = 1;
            }
        }
        end_index--;
        for (int i = end_index; i > start_index; i--){
            if (vec[i-1] > vec[i]){
                tmp = vec[i];
                vec[i] = vec[i-1];
                vec[i-1] = tmp;
                flag = 1;
            }
        }
        start_index++;
        if (!flag) return;
    }
}

// Гравитационная сортировка
void bead_sort(int * vec, int size){
    int max = vec[0];
    for(int i = 0; i < size; i++)
        if(vec[i] > max) max = vec[i];
    int ** beads = (int**)malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++){
        beads[i] = (int*)malloc(max * sizeof(int));
        memset(beads[i], 0, max * sizeof(int));
    }
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < vec[i]; j++) 
            beads[i][j] = 1;
    
    for (int j = 0; j < max; j++) { 
        int sum = 0; 
        for (int i = 0; i < size; i++) { 
            sum += beads[i][j]; 
            beads[i][j] = 0; 
        } 
        for (int i = size - sum; i < size; i++) 
            beads[i][j] = 1; 
    } 
    for (int i = 0; i < size; i++) { 
        int sum = 0; 
        for (int j = 0; j < max; j++) 
            sum += beads[i][j]; 
        vec[i] = sum; 
    }
    for (int i = 0; i < size; i++)
        free(beads[i]);
    free(beads);
}

int is_sorted_ascending(int *array, int n) {
    if (array == NULL || n == 0) 
        return 1;

    for (int i = 1; i < n; i++) 
        if (array[i-1] > array[i]) 
            return 0;
    return 1;
}

void input(int * vec, int n){
    printf("List input: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &vec[i]);
}

void output(int * vec, int n){
    printf("///output///\n");
    for (int i = 0; i < n; i++)
        printf("%d ", vec[i]);
    printf("\n");
}

int * random_array (int * n){
    srand(time(NULL));
    int min = 1000, max = 10000;
    if (*n < 1){
        *n = (rand() % (max - min + 1)) + min;
        printf("Size of list: %d\n", *n);
        }
    int * array = (int*)malloc(*n * sizeof(int));
    for (int i = 0; i < *n; i++) {
        array[i] = rand();
        // printf("%d ", array[i]);
    }
    printf("\n");
    return array;
}

void testing(int test_number){
    int counter = 1;
    double sheker_sum = 0, bead_sum = 0;
    printf("///TESTING///\nn sheker bead\n");
    while (counter <= test_number){
            int n = counter*100, * array = random_array(&n);
            int * vector = (int*)malloc(n * sizeof(int));
            memcpy(vector, array, n * sizeof(int));
            clock_t start_sheker = clock();
            sheker_sort(vector, n);
            clock_t end_sheker = clock();
            double time_sheker = (double)(end_sheker - start_sheker) / CLOCKS_PER_SEC;
            memcpy(vector, array, n * sizeof(int));
            clock_t start_bead = clock();
            bead_sort(vector, n);
            clock_t end_bead = clock();
            double time_bead = (double)(end_bead - start_bead) / CLOCKS_PER_SEC;   
            printf("%d %.3lf %.3lf", n, time_sheker, time_bead);
            counter ++;
            sheker_sum += time_sheker;
            bead_sum += time_bead;
    }
    printf("\nSummary: sheker: %.2lf, bead: %.2lf\n", sheker_sum, bead_sum);
}

int main(){
    int n = 0, choise, *array;
    printf("Print:\n <1> for random input\n <2> for manual input\n <3> for algorithm test\n");
    scanf("%d", &choise);
    if (choise == 2){
        printf("Size input: ");
        scanf("%d", &n);
        array = (int*)malloc(n * sizeof(int));
        input(array, n);
    }
    else if (choise==1) {
        array = random_array(&n);
    }
    else if (choise == 3){
        int counter = 0, test_number;
        printf("Number of tests input: ");
        scanf("%d", &test_number);
        testing(test_number);
        return 1;
    }
    else{
        printf("Wron input\n");
        return 1;
    }
    int * vector = (int*)malloc(n * sizeof(int));
    memcpy(vector, array, n * sizeof(int));
    clock_t start_sheker = clock();
    sheker_sort(vector, n);
    clock_t end_sheker = clock();
    printf("\nsheker sorting algorithm:\n");
    double time_sheker = (double)(end_sheker - start_sheker) / CLOCKS_PER_SEC;
    printf("Sheker Sort took %f seconds to sort %d elements.\n", time_sheker, n);
    if (is_sorted_ascending(vector, n))
        printf("List is sorted\n");
    else
        printf("List is not sorted\n");
    
    memcpy(vector, array, n * sizeof(int));
    clock_t start_bead = clock();
    bead_sort(vector, n);
    clock_t end_bead = clock();
    printf("\nbead sorting algorithm:\n");
    double time_bead = (double)(end_bead - start_bead) / CLOCKS_PER_SEC;
    printf("Bead Sort took %f seconds to sort %d elements.\n", time_bead, n);
    if (is_sorted_ascending(vector, n))
        printf("List is sorted\n");
    else
        printf("List is not sorted\n");

    free(array);
    free(vector);
    return 0;
}
