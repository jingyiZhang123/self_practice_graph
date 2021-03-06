
#include "dense_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern DenseGraph_p DenseGraph_Init(const int num_vertexes, const bool directed);
extern void DenseGraph_Destruct(DenseGraph_p dg);
extern int V(DenseGraph_p dg);
extern int E(DenseGraph_p dg);
extern void DenseGraph_AddEdge(DenseGraph_p dg, int v, int w);
extern bool DenseGraph_HasEdge(DenseGraph_p dg, int v, int w);
extern void DenseGraph_PrintGraph(const DenseGraph_p dg);

extern DenseIterator_p DenseIterator_Init(DenseGraph_p g, int v);
extern int DenseIterator_begin(DenseIterator_p iter);
extern int DenseIterator_next(DenseIterator_p iter);
extern bool DenseIterator_end(DenseIterator_p iter);


DenseGraph_p DenseGraph_Init(const int num_vertexes, const bool directed){
    DenseGraph_p new_dg = malloc(sizeof(DenseGraph_t));
    assert(new_dg != NULL);
    new_dg->num_vertexes = num_vertexes;
    new_dg->num_edges = 0;

    new_dg->directed = directed;

    new_dg->graph = malloc(sizeof(bool*) * num_vertexes);
    for (int i=0; i<num_vertexes; i++)
        new_dg->graph[i] = malloc(sizeof(bool) * num_vertexes);

    for (int i=0; i<num_vertexes; i++)
        for (int j=0; j<num_vertexes; j++)
            new_dg->graph[i][j] = false;

    return new_dg;
}


void DenseGraph_Destruct(DenseGraph_p dg){
    for (int i=0; i < dg->num_vertexes; i++)
        free(dg->graph[i]);
    free(dg->graph);
    free(dg);
    return;
}


int V(DenseGraph_p dg){
    return dg->num_vertexes;
}


int E(DenseGraph_p dg){
    return dg->num_edges;
}

//v, w: indexes of two vertexes
void DenseGraph_AddEdge(DenseGraph_p dg, int v, int w){
    assert(v >= 0 && v < dg->num_vertexes);
    assert(w >= 0 && w < dg->num_vertexes);

    if(DenseGraph_HasEdge(dg, v, w))
        return;

    dg->graph[v][w] = true;
    if(dg->directed == false)
        dg->graph[w][v] = true;
    dg->num_edges ++;
}

bool DenseGraph_HasEdge(DenseGraph_p dg, int v, int w){
    assert(v >= 0 && v < dg->num_vertexes);
    assert(w >= 0 && w < dg->num_vertexes);
    return dg->graph[v][w];
}

void DenseGraph_PrintGraph(const DenseGraph_p dg){
    for (int i=0; i < dg->num_vertexes; i++) {
        for (int j=0; j < dg->num_vertexes; j++)
            printf("%d ", dg->graph[i][j]);
        printf("\n");
    }
    return ;
}


DenseIterator_p DenseIterator_Init(DenseGraph_p g, int v){
    DenseIterator_p iter = malloc(sizeof(DenseIterator_t));
    assert(iter != NULL);

    iter->G = g;
    iter->v = v;
    iter->index = -1;
}

int DenseIterator_begin(DenseIterator_p iter){
    iter->index = -1;
    return DenseIterator_next(iter);
}

int DenseIterator_next(DenseIterator_p iter){
    for (iter->index += 1; iter->index < iter->G->num_vertexes; iter->index ++) {
        if(iter->G->graph[iter->v][iter->index])
            return iter->index;
    }
    return -1;
}

bool DenseIterator_end(DenseIterator_p iter){
    return iter->index >= iter->G->num_vertexes;
}
