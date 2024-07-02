#include "sort.h"
#include <string.h>
#include <stdlib.h>

void BubbleSort(Entry* entry, int size) { // sorts alphabetically using BubbleSort
    int i;
    int j;
    Entry temp;
    for (i = 0; i < size - 1; i++) {
      for (j = 0; j < size - i - 1; j++) {
         if (strcmp(entry[j].origin, entry[j + 1].origin) > 0 || (strcmp(entry[j].origin, entry[j + 1].origin) == 0 && strcmp(entry[j].destination, entry[j + 1].destination) > 0)) {
            temp = entry[j];
            entry[j] = entry[j + 1];
            entry[j + 1] = temp;
         }
      }
   }
}

void QuickSort(Entry* entry, int size) { // sorts alphabetically using QuickSort
    if (size <= 1) { // base case!
        return;
    }

    Entry pivot = entry[size - 1]; // sets pivot as last value
    int i = -1; // begins before first value
    int j;
    Entry temp;

    for (j = 0; j < size - 1; ++j) {
        if (strcmp(entry[j].origin, pivot.origin) < 0 || (strcmp(entry[j].origin, pivot.origin) == 0 && strcmp(entry[j].destination, pivot.destination) < 0)) {
            ++i;
            temp = entry[i];
            entry[i] = entry[j];
            entry[j] = temp;
        }
    }

    temp = entry[i + 1]; // moves pivot
    entry[i + 1] = entry[size - 1];
    entry[size - 1] = temp;

    QuickSort(entry, i + 1); // recursive call
    QuickSort(entry + i + 2, size - i - 2);
}

void MergeSort(Entry* entry, int size) { // sorts alphabetically using Merge Sort
    if (size <= 1) { // base case!
        return;
    }

    int middle = size / 2; // divides into halves to find the midpoint
    int i = 0;
    int j = middle;
    int k = 0;
    
    MergeSort(entry, middle); // left half
    MergeSort(entry + middle, size - middle); // right half

    Entry* temp = malloc(size * sizeof(Entry)); // allocates memory
    while (i < middle && j < size) {
        if (strcmp(entry[i].origin, (entry + j)->origin) < 0 || (strcmp(entry[i].origin, (entry + j)->origin) == 0 && strcmp(entry[i].destination, (entry + j)->destination) <= 0)) {
            temp[k++] = entry[i++];
        }
        else {
            temp[k++] = entry[j++];
        }
    }
    while (i < middle) {
        temp[k++] = entry[i++];
    }
    while (j < size) {
        temp[k++] = entry[j++];
    }

    for (int m = 0; m < size; ++m) { // copies merged elemnts back to original array
        entry[m] = temp[m];
    }

    free(temp); // frees memory
}