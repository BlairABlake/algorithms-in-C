//
// Created by ryousuke kaga on 2023/10/06.
//

#include "queue.h"

int queue_enqueue(Queue* queue, const void* data) {
    return list_ins_next(queue, queue->tail, data);
}

int queue_dequeue(Queue* queue, void** data) {
    return list_rem_next(queue, NULL, data); // NULL indicates the head
}