//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TEST_QUEUE_H
#define MYALGORITHMS_TEST_QUEUE_H

#include "test.h"

TEST(test_queue_FIFO) {
    Queue queue;
    queue_init(&queue, NULL);

    int xs[] = {1, 2, 3, 4, 5};

    for(int i=0; i < 5; i++) {
        queue_enqueue(&queue, &xs[i]);
    }

    int* tmp;
    for(int i=0; i < 5; i++) {
        queue_dequeue(&queue, (void **)&tmp);
        munit_assert(tmp == &xs[i]);
    }

    return MUNIT_OK;
}

#define QUEUE_TESTS \
    {              \
        "queue_FIFO", \
        test_queue_FIFO, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }


#endif //MYALGORITHMS_TEST_QUEUE_H
