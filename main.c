#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "dense_graph.h"
#include "sparse_graph.h"

void DenseGraph_Test(char* filename){
    printf("------------------------------\n");
    FILE *fp;
    char buffer[256];
    fp = fopen(filename, "r");
    char* pch;
    DenseGraph_p sg =  DenseGraph_Init(14, false);
    while(fgets(buffer, 255, (FILE*) fp) != NULL){
        pch = strtok(buffer, " \n");
        int v = atoi(pch);
        pch = strtok(NULL, " \n");
        int w= atoi(pch);
        DenseGraph_AddEdge(sg, v, w);
    }
    fclose(fp);
    DenseGraph_PrintGraph(sg);
    printf("------------------------------\n");
}

void SparseGraph_Test(char* filename){
    printf("------------------------------\n");
    FILE *fp;
    char buffer[256];
    fp = fopen(filename, "r");
    char* pch;
    SparseGraph_p sg =  SparseGraph_Init(14, false);
    while(fgets(buffer, 255, (FILE*) fp) != NULL){
        pch = strtok(buffer, " \n");
        int v = atoi(pch);
        pch = strtok(NULL, " \n");
        int w= atoi(pch);
        SparseGraph_AddEdge(sg, v, w);
    }
    fclose(fp);
    SparseGraph_PrintGraph(sg);
    printf("------------------------------\n");

}

void Test1(){
    char* file1 = "./graph1.txt";
    char* file2 = "./graph2.txt";

    DenseGraph_Test(file1);
    DenseGraph_Test(file2);

    SparseGraph_Test(file1);
    SparseGraph_Test(file2);

}

int main(int argc, char *argv[])
{

    return 0;
}
