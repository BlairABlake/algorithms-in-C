//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_SET_H
#define MYALGORITHMS_SET_H

#include <stdlib.h>
#include "list.h"

typedef List Set;

void set_init(Set* set, int (*match)(const void* key1, const void* key2), void (*destroy)(void* data));
#define set_destroy list_destroy
int set_insert(Set* set, const void* data);
int set_remove(Set* set, void** data);
int set_is_member(const Set* set, const void* data);
#define set_size(set) ((set)->size)

#endif //MYALGORITHMS_SET_H
