//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_HEAP_H
#define MYALGORITHMS_HEAP_H

#include <stdlib.h>
#include <string.h>

typedef struct Heap_ {
    int size;
    int (*compare)(const void* key1, const void* key2); // return 0 > if key1 is bigger
    int (*destroy)(void* data);
    void** tree;
} Heap;

void heap_init(Heap* heap, int (*compare)(const void* key1, const void* key2), int (*destroy)(void* data));
void heap_destroy(Heap* heap);
int heap_insert(Heap* heap, const void* data);
int heap_extract(Heap* heap, void** data);
#define heap_size(heap) ((heap)->size)

#endif //MYALGORITHMS_HEAP_H
