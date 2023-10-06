//
// Created by ryousuke kaga on 2023/10/06.
//

#include "graph.h"
#include "stdio.h"

void graph_init(Graph* graph, int (*match)(const void* key1, const void* key2), void (*destroy)(void* data)) {
    graph->vcount = 0;
    graph->ecount = 0;
    graph->match = match;
    graph->destroy = destroy;
    list_init(&graph->adjlists, NULL);
}

void graph_destroy(Graph* graph) {
    AdjList* adjlist;

    while(list_size(&graph->adjlists) > 0) {
        if(list_rem_next(&graph->adjlists, NULL, (void**)&adjlist) == 0) {
            set_destroy(&adjlist->adjacent);

            if(graph->destroy != NULL)
                graph->destroy(adjlist->vertex);

            free(adjlist);
        }
    }

    list_destroy(&graph->adjlists);

    memset(graph, 0, sizeof(Graph));
}

int graph_ins_vertex(Graph* graph, const void* data) {
    int retval;
    ListElm* element;
    AdjList* adjlist;

    // prevent duplication
    for(element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if(graph->match(data, adjlist_vertex(element)))
            return 1;
    }

    if((adjlist = (AdjList*)malloc(sizeof(AdjList))) == NULL)
        return -1;

    adjlist->vertex = (void*)data;
    set_init(&adjlist->adjacent, graph->match, NULL);
    if((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists), adjlist)))
        return retval;

    graph->vcount++;
    return 0;
}

int graph_ins_edge(Graph* graph, const void* data1, const void* data2) {
    ListElm* element;
    int retval;

    //check the vertex with data1 and data2 exist
    for(element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if(graph->match(data2, ((AdjList*)list_data(element))->vertex))
            break;
    }

    if(element == NULL) // if not found
        return -1;

    for(element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if(graph->match(data1, ((AdjList*)list_data(element))->vertex))
            break;
    }

    if(element == NULL) // if not found
        return -1;

    if((retval = set_insert(&((AdjList*)list_data(element))->adjacent, data2)))
        return retval;

    graph->ecount++;
    return 0;
}

int graph_rem_vertex(Graph* graph, void** data) {
    ListElm *element, *temp, *prev;
    AdjList* adjlist;
    int found;

    prev = NULL;
    found = 0;
    for(element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if(set_is_member(&adjlist_adjacent(element), *data))
            return -1;

        if(graph->match(*data, adjlist_vertex(element))) {
            temp = element;
            found = 1;
        }

        if(!found)
            prev = element;
    }

    if(!found)
        return -1;

    if(set_size(&adjlist_adjacent(temp)) > 0) // if connected
        return -1;

    if(list_rem_next(&graph->adjlists, prev, (void**)&adjlist))
        return -1;

    *data = adjlist->vertex;
    free(adjlist);

    graph->vcount--;
    return 0;
}

int graph_rem_edge(Graph* graph, void* data1, void** data2) {
    ListElm* element;

    for(element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if(graph->match(data1, adjlist_vertex(element)))
            break;
    }

    if(element == NULL)
        return -1;

    if(set_remove(&adjlist_adjacent(element), data2))
        return -1;

    graph->ecount--;
    return 0;
}

int graph_adjlist(const Graph* graph, const void* data, AdjList** adjlist) {
    ListElm *element;

    for(element = list_head(&graph->adjlists); element != NULL; element = list_next(element)) {
        if(graph->match(data, adjlist_vertex(element)))
            break;
    }

    if(element == NULL)
        return -1;

    *adjlist = list_data(element);
    return 0;
}

int graph_is_adjacent(const Graph* graph, const void* data1, const void* data2) {
    AdjList* adjlist;

    adjlist = NULL;

    if(graph_adjlist(graph, data1, &adjlist))
        return 0;

    return set_is_member(&adjlist->adjacent, data2);
}
