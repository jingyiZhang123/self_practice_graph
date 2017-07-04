
#ifndef DENSE_GRAPH_H
#define DENSE_GRAPH_H

#include <stdbool.h>

typedef struct DenseGraph{
    int num_vertexes;
    int num_edges;

    bool directed;

    bool** graph;

}DenseGraph_t;

typedef DenseGraph_t* DenseGraph_p;

extern DenseGraph_p DenseGraph_Init(const int num_vertexes, const bool directed);
extern void DenseGraph_Destruct(DenseGraph_p dg);
extern int V(DenseGraph_p dg);
extern int E(DenseGraph_p dg);
extern void DenseGraph_AddEdge(DenseGraph_p dg, int v, int w);
extern bool DenseGraph_HasEdge(DenseGraph_p dg, int v, int w);
extern void DenseGraph_PrintGraph(const DenseGraph_p dg);


#endif
