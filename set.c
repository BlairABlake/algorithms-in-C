//
// Created by ryousuke kaga on 2023/10/06.
//

#include "set.h"

void set_init(Set* set, int (*match)(const void* key1, const void* key2), void (*destroy)(void* data)) {
    list_init(set, destroy);
    set->match = match;
}

int set_insert(Set* set, const void* data) {
    if(set_is_member(set, data))
        return 1;

    return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set* set, void** data) {
    ListElm *member, *prev;

    prev = NULL;

    for(member = list_head(set); member != NULL; member = list_next(member)) {
        if(set->match(*data, list_data(member)))
            break;
        prev = member;
    }

    if(member == NULL)
        return -1;

    return list_rem_next(set, prev, data);
}
int set_is_member(const Set* set, const void* data) {
    ListElm *member;

    for(member = list_head(set); member != NULL; member = list_next(member)) {
        if(set->match(data, list_data(member)))
            return 1;
    }

    return 0;
}