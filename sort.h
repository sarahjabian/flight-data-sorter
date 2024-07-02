#ifndef SORT_H
#define SORT_H

typedef struct Entry { // creates a struct called Entry
    char origin[4]; // length is 4 because it's 3 characters + "\0"
    char destination[4];
    char etc[300];
} Entry;

void BubbleSort(Entry* entry, int size);
void QuickSort(Entry* entry, int size);
void MergeSort(Entry* entry, int size);

#endif