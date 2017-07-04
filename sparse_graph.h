
#ifndef SPARSE_GRAPH_H
#define SPARSE_GRAPH_H

#include <stdbool.h>

typedef struct Node Node_t;
typedef Node_t* Node_p;

struct Node{
    int value;
    Node_p next;
};


typedef struct SparseGraph{
    int num_vertexes;
    int num_edges;

    bool directed;

    Node_p* graph;

}SparseGraph_t;
typedef SparseGraph_t* SparseGraph_p;

extern SparseGraph_p SparseGraph_Init(const int num_vertexes, const bool directed);
extern void SparseGraph_AddEdge(SparseGraph_p sg, int v, int w);
extern bool SparseGraph_HasEdge(SparseGraph_p sg, int v, int w);
extern void SparseGraph_PrintGraph(const SparseGraph_p sg);



#endif
