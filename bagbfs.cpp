#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Bag.cpp"

typedef struct graphstruct { // A graph in compressed-adjacency-list (CSR) form
    int nv;            // number of vertices
    int ne;            // number of edges
    int *nbr;          // array of neighbors of all vertices
    int *firstnbr;     // index in nbr[] of first neighbor of each vtx
} graph;


int read_edge_list (int **tailp, int **headp) {
    int max_edges = 1000000;
    int nedges, nr, t, h;
    *tailp = (int *) calloc(max_edges, sizeof(int));
    *headp = (int *) calloc(max_edges, sizeof(int));
    nedges = 0;
    nr = scanf("%i %i",&t,&h);
    while (nr == 2) {
        if (nedges >= max_edges) {
            printf("Limit of %d edges exceeded.\n",max_edges);
            exit(1);
        }
        (*tailp)[nedges] = t;
        (*headp)[nedges++] = h;
        nr = scanf("%i %i",&t,&h);
    }
    return nedges;
}

//create a graph from a list of edges
graph * graph_from_edge_list (int *tail, int* head, int nedges) {
    graph *G;
    int i, e, v, maxv;
    G = (graph *) calloc(1, sizeof(graph));
    G->ne = nedges;
    maxv = 0;
    
    // count vertices
    for (e = 0; e < G->ne; e++) {
        if (tail[e] > maxv) maxv = tail[e];
        if (head[e] > maxv) maxv = head[e];
    }
    G->nv = maxv+1;
    G->nbr = (int *) calloc(G->ne, sizeof(int));
    G->firstnbr = (int *) calloc(G->nv+1, sizeof(int));
    
    // count neighbors of vertex v in firstnbr[v+1],
    for (e = 0; e < G->ne; e++) G->firstnbr[tail[e]+1]++;
    
    // cumulative sum of neighbors gives firstnbr[] values
    for (v = 0; v < G->nv; v++) G->firstnbr[v+1] += G->firstnbr[v];
    
    // pass through edges, slotting each one into the CSR structure
    for (e = 0; e < G->ne; e++) {
        i = G->firstnbr[tail[e]]++;
        G->nbr[i] = head[e];
    }
    // the loop above shifted firstnbr[] left; shift it back right
    for (v = G->nv; v > 0; v--) G->firstnbr[v] = G->firstnbr[v-1];
    G->firstnbr[0] = 0;
    return G;
}

//print a CSR graph
void print_CSR_graph (graph *G) {
    int vlimit = 20;
    int elimit = 50;
    int e,v;
    printf("\nGraph has %d vertices and %d edges.\n",G->nv,G->ne);
    printf("firstnbr =");
    if (G->nv < vlimit) vlimit = G->nv;
    for (v = 0; v <= vlimit; v++) printf(" %d",G->firstnbr[v]);
    if (G->nv > vlimit) printf(" ...");
    printf("\n");
    printf("nbr =");
    if (G->ne < elimit) elimit = G->ne;
    for (e = 0; e < elimit; e++) printf(" %d",G->nbr[e]);
    if (G->ne > elimit) printf(" ...");
    printf("\n\n");
}
