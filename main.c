#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

int main() {

    FILE *file = NULL;
    file = fopen("airport_smol.csv", "r"); // opens file
    if (file == NULL) {
        printf("Couldn't open file.");
        return 1;
    }

    int size = 0;
    char buffer[500];
    char firstLine[500]; // first label row
    
    while (fgets(buffer, sizeof(buffer), file)) { // calculates size
        size++;
    }

    rewind(file); // resets pointer to beginning of file

    fgets(firstLine, sizeof(firstLine), file); // sets aside first line
    size = size - 1; // calculates size minus the first line

    Entry* data = malloc(size * sizeof(Entry)); // allocates memory
    for (int i = 0; i < size; ++i) {
        buffer[0] = '\0'; // clears buffer
        fgets(buffer, sizeof(buffer), file); // reads a line from the file and puts it into buffer
        sscanf(buffer, "\"%3[^\"]\",\"%3[^\"]\",%300[^\n]", data[i].origin, data[i].destination, data[i].etc);
    }

    fclose(file); // closes file

    clock_t start, end; // for timing purposes
    double runtimes[3]; // for ranking purposes
    char *names[] = {"BubbleSort", "QuickSort", "MergeSort"};

    // BUBBLE SORT
    Entry *bubble = malloc(size * sizeof(Entry)); // allocates memory for bubble
    for (int i = 0; i < size; ++i) { 
        bubble[i] = data[i]; // copies data into bubble
    } 
    start = clock();
    BubbleSort(bubble, size); // performs the sorting algorithm
    end = clock();
    runtimes[0] = ((double)(end - start))/CLOCKS_PER_SEC; // calculates function's runtime
    
    FILE *bubble_file = NULL;
    bubble_file = fopen("bubble_sort.csv", "w"); // writes into a csv
    if (bubble_file == NULL) {
        printf("Couldn't open file.");
        return 1;
    }
    fprintf(bubble_file, "%s", firstLine); // prints first label row
    for (int i = 0; i < size; ++i) { // prints bubble sorted data
        fprintf(bubble_file, "\"%s\",\"%s\",%s\n", bubble[i].origin, bubble[i].destination, bubble[i].etc);
    }
    fclose(bubble_file);

    free(bubble); // frees allocated memory
    printf("BubbleSort: Complete!\n");


    // QUICK SORT (same structure as bubble so no need for comments)
    Entry *quick = malloc(size * sizeof(Entry));
    for (int i = 0; i < size; ++i) {
        quick[i] = data[i];
    }
    start = clock();
    QuickSort(quick, size);
    end = clock();
    runtimes[1] = ((double)(end - start))/CLOCKS_PER_SEC;

    FILE *quick_file = NULL;
    quick_file = fopen("quick_sort.csv", "w");
    if (quick_file == NULL) {
        printf("Couldn't open file.");
        return 1;
    }
    fprintf(quick_file, "%s", firstLine);
    for (int i = 0; i < size; ++i) {
        fprintf(quick_file, "\"%s\",\"%s\",%s\n", quick[i].origin, quick[i].destination, quick[i].etc);
    }
    fclose(quick_file);

    free(quick);
    printf("QuickSort: Complete!\n");

    // MERGE SORT (also same structure as bubble)
    Entry *merge = malloc(size * sizeof(Entry));
    for (int i = 0; i < size; ++i) {
        merge[i] = data[i];
    }
    start = clock();
    MergeSort(merge, size);
    end = clock();
    runtimes[2] = ((double)(end - start))/CLOCKS_PER_SEC;

    FILE *merge_file = NULL;
    merge_file = fopen("merge_sort.csv", "w");
    if (merge_file == NULL) {
        printf("Couldn't open file.");
        return 1;
    }
    fprintf(merge_file, "%s", firstLine);
    for (int i = 0; i < size; ++i) {
        fprintf(merge_file, "\"%s\",\"%s\",%s\n", merge[i].origin, merge[i].destination, merge[i].etc);
    }
    fclose(merge_file);

    free(merge);
    printf("MergeSort: Complete!\n");


    // FINAL TIMES
    printf("\nFinal Times\n");

    for (int i = 0; i < 3; ++i) { // determines ranking
        for (int j = i + 1; j < 3; ++j) {
            if (runtimes[i] > runtimes[j]) {
                double temp = runtimes[i];
                runtimes[i] = runtimes[j];
                runtimes[j] = temp;
                char *tempName = names[i];
                names[i] = names[j];
                names[j] = tempName;
            }
        }
    }

    for (int i = 1; i <= 3; ++i) { // prints ranking
        printf("%d. %s: %.6lf seconds\n", i, names[i - 1], runtimes[i - 1]);
    }

    free(data); 
    // frees data so its not sorted

    return 0;
}