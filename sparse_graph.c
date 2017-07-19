
#include "sparse_graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

extern SparseGraph_p SparseGraph_Init(const int num_vertexes, const bool directed);
extern void SparseGraph_AddEdge(SparseGraph_p sg, int v, int w);
extern bool SparseGraph_HasEdge(SparseGraph_p sg, int v, int w);
extern void SparseGraph_PrintGraph(const SparseGraph_p sg);

extern adjIterator_p adjIterator_Init(SparseGraph_p g, int v);
extern int adjIterator_begin(adjIterator_p iter);
extern int adjIterator_next(adjIterator_p iter);
extern bool adjIterator_end(adjIterator_p iter);



static Node_p _add_node(Node_p head, Node_p new_node);


SparseGraph_p SparseGraph_Init(const int num_vertexes, const bool directed){
    SparseGraph_p new_sg = malloc(sizeof(SparseGraph_t));
    assert(new_sg != NULL);
    new_sg->num_vertexes = num_vertexes;
    new_sg->num_edges = 0;

    new_sg->directed = directed;

    new_sg->graph = malloc(sizeof(Node_p) * num_vertexes);
    for (int i=0; i<num_vertexes; i++)
        new_sg->graph[i] = NULL;

    return new_sg;
}


void SparseGraph_AddEdge(SparseGraph_p sg, int v, int w){
    if(SparseGraph_HasEdge(sg, v, w))
        return;

    Node_p new_node = malloc(sizeof(Node_t));
    new_node->value = w;
    new_node->next = NULL;

    sg->graph[v] = _add_node(sg->graph[v], new_node);
    if(sg->directed == false && v != w){
        Node_p new_node2 = malloc(sizeof(Node_t));
        new_node2->value = v;
        new_node2->next = NULL;
        sg->graph[w] = _add_node(sg->graph[w], new_node2);
    }
    sg->num_edges ++;
}

bool SparseGraph_HasEdge(SparseGraph_p sg, int v, int w){
    assert(v >= 0 && v < sg->num_vertexes);
    assert(w >= 0 && w < sg->num_vertexes);

    if(sg->graph[v] == NULL)
        return false;
    Node_p head;
    for(head = sg->graph[v]; head!=NULL; head = head->next){
        if(head->value == w)
            return true;
    }
    return false;

}

void SparseGraph_PrintGraph(const SparseGraph_p sg){
    for (int i=0; i<sg->num_vertexes; i++) {
        printf("%d: ", i);
        for (Node_p node=sg->graph[i]; node != NULL; node=node->next)
            printf("%d ", node->value);
        printf("\n");
    }
}


adjIterator_p adjIterator_Init(SparseGraph_p g, int v){
    adjIterator_p iter = malloc(sizeof(adjIterator_t));
    assert(iter != NULL);
    iter->G = g;
    iter->v = v;
    iter->index = 0;

    return iter;
}

int adjIterator_begin(adjIterator_p iter){
    iter->index = 0;
    if (iter->G->graph[iter->v] != NULL)
        return iter->G->graph[iter->v]->value;
    return -1;
}

int adjIterator_next(adjIterator_p iter){
    iter->index ++;
    Node_p node=iter->G->graph[iter->v];
    if (node == NULL)
        return -1;
    for (int i = 0; i < iter->index; i++) {
        node = node->next;
        if (node == NULL)
            return -1;
    }
    return node->value;
}

bool adjIterator_end(adjIterator_p iter){
    Node_p node=iter->G->graph[iter->v];
    if (node == NULL)
        return true;
    for (int i = 0; i < iter->index; i++) {
        node = node->next;
        if (node == NULL)
            return true;
    }
    return false;
}


Node_p _add_node(Node_p head, Node_p new_node){
    if(head == NULL)
        return new_node;
    Node_p temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = new_node;
    return head;
}
