//
// Created by ryousuke kaga on 2023/10/06.
//

#ifndef MYALGORITHMS_TEST_GRAPH_H
#define MYALGORITHMS_TEST_GRAPH_H

#include "test.h"

int int_match(const void* i1, const void* i2) {
    return *(int*)i1 == *(int*)i2;
}

TEST(test_graph_vertex_insertion) {
    Graph graph;
    graph_init(&graph, int_match, NULL);
    int vertices[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        munit_assert(graph_ins_vertex(&graph, &vertices[i]) == 0);
    }

    return MUNIT_OK;
}

TEST(test_graph_edge_insertion) {
    Graph graph;
    graph_init(&graph, int_match, NULL);
    int vertices[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        munit_assert(graph_ins_vertex(&graph, &vertices[i]) == 0);
    }

    munit_assert(graph_ins_edge(&graph, &vertices[0], &vertices[1]) == 0);
    munit_assert(set_is_member(&adjlist_adjacent(graph.adjlists.head), &vertices[1]));
    munit_assert_false(set_is_member(&adjlist_adjacent(graph.adjlists.head->next), &vertices[0]));

    return MUNIT_OK;
}

TEST(test_graph_rem_vertex_fail_if_connected) {
    Graph graph;
    graph_init(&graph, int_match, NULL);
    int vertices[] = {1, 2, 3, 4};
    for(int i=0; i < 4; i++) {
        graph_ins_vertex(&graph, &vertices[i]);
    }

    graph_ins_edge(&graph, &vertices[0], &vertices[1]);

    int* target = &vertices[0];
    munit_assert(graph_rem_vertex(&graph, (void**)&target) == -1);

    return MUNIT_OK;
}

TEST(test_graph_rem_vertex) {
    Graph graph;
    graph_init(&graph, int_match, NULL);

    int vertices[] = {1, 2, 3, 4};
    for(int i=0; i < 4; i++) {
        graph_ins_vertex(&graph, &vertices[i]);
    }

    graph_ins_edge(&graph, &vertices[0], &vertices[1]);

    int* target = &vertices[2];

    munit_assert(graph_rem_vertex(&graph, (void**)&target) == 0);

    return MUNIT_OK;
}

TEST(test_graph_rem_edge_fail_if_not_found) {
    Graph graph;
    graph_init(&graph, int_match, NULL);

    int vertices[] = {1, 2, 3, 4};
    for(int i=0; i < 4; i++) {
        graph_ins_vertex(&graph, &vertices[i]);
    }

    graph_ins_edge(&graph, &vertices[0], &vertices[1]);

    int* target = &vertices[2];

    munit_assert(graph_rem_edge(&graph, &vertices[3], (void**)&target) == -1);
    munit_assert(graph_rem_edge(&graph, &vertices[0], (void**)&target) == -1);

    return MUNIT_OK;
}

TEST(test_graph_rem_edge) {
    Graph graph;
    graph_init(&graph, int_match, NULL);

    int vertices[] = {1, 2, 3, 4};
    for(int i=0; i < 4; i++) {
        graph_ins_vertex(&graph, &vertices[i]);
    }

    graph_ins_edge(&graph, &vertices[0], &vertices[1]);

    int* target = &vertices[1];

    munit_assert(graph_rem_edge(&graph, &vertices[0], (void**)&target) == 0);
    munit_assert_false(graph_is_adjacent(&graph, &vertices[0], &vertices[1]));

    return MUNIT_OK;
}

#define GRAPH_TESTS \
    {              \
        "graph_rem_vertex_fail_if_connected", \
        test_graph_rem_vertex_fail_if_connected, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
    {              \
        "graph_rem_vertex", \
        test_graph_rem_vertex, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
   {              \
        "graph_vertex_insertion", \
        test_graph_vertex_insertion, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
   {              \
        "graph_edge_insertion", \
        test_graph_edge_insertion, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
       {              \
        "graph_edge_removal_fail_if_not_found", \
        test_graph_rem_edge_fail_if_not_found, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    },              \
   {              \
        "graph_edge_removal", \
        test_graph_rem_edge, \
        NULL,      \
        NULL,      \
        MUNIT_TEST_OPTION_NONE, \
        NULL\
    }

#endif //MYALGORITHMS_TEST_GRAPH_H
