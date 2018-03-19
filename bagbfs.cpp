#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<cilk/cilk.h>

#include "Bag.hpp"
#include "Pennant.hpp"

const int GRAINSIZE = 100;

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

void process_layer(Bag *in_bag, Bag *out_bag, d){
    
    if(in_bag.getPennantVectorSize < GRAINSIZE){
        for (int i=0; i<in_bag.getPennantVectorSize(); i++){
            vector<int> vertices = in_bag[i].dumpVertices();
            cilk_for (int k = 0; k < vertices.size(); k++){
                //if distance of v is -1, make v distance = d+1 and insert to out_bag
            }
        }
        return;
    }
    new_bag = in_bag.split();
    cilk_spawn process_layer(new_bag, out_bag, d);
    process_layer(in_bag, out_bag, d);
    cilk_sync;
}

void pbfs(int s, graph *G, int **levelp, int *nlevelsp, int **levelsizep, int **parentp){
    
    int *level, *levelsize, *parent;
    int thislevel;
    vector<Bag> bags;
    int d = 0;
    level = *levelp = (int *) calloc(G->nv, sizeof(int));
    levelsize = *levelsizep = (int *) calloc(G->nv, sizeof(int));
    parent = *parentp = (int *) calloc(G->nv, sizeof(int));

    for (v = 0; v < G->nv; v++) level[v] = -1;
    for (v = 0; v < G->nv; v++) parent[v] = -1;
    
    // assign the starting vertex level 0
    thislevel = 0;
    level[s] = 0;
    levelsize[0] = 1;
    
    Bag bag = new Bag();
    bag.add(s);
    bags.push_back(bag);

    while(bags[d].getPennantVectorSize() > 0){
        //reducer
        Bag new_bag = new Bag();
        bags.push_back(new_bag);
        process_layer(bags[d], bags[d+1], d);
        d++;
    }
    
}

int main (int argc, char* argv[]) {
    graph *G;
    int *level, *levelsize, *parent;
    int *tail, *head;
    int nedges;
    int nlevels;
    int startvtx;
    int i, v, reached;
    
    if (argc == 2) {
        startvtx = atoi (argv[1]);
    } else {
        printf("usage:   bagbfs <startvtx> < <edgelistfile>\n");
        printf("example: cat sample.txt | ./bfstest 1\n");
        exit(1);
    }
    nedges = read_edge_list (&tail, &head);
    G = graph_from_edge_list (tail, head, nedges);
    free(tail);
    free(head);
    print_CSR_graph (G);
    
    printf("Starting vertex for BFS is %d.\n\n",startvtx);
    pbfs (startvtx, G, &level, &nlevels, &levelsize, &parent);
    
    reached = 0;
    for (i = 0; i < nlevels; i++) reached += levelsize[i];
    printf("Breadth-first search from vertex %d reached %d levels and %d vertices.\n",
           startvtx, nlevels, reached);
    for (i = 0; i < nlevels; i++) printf("level %d vertices: %d\n", i, levelsize[i]);
    if (G->nv < 20) {
        printf("\n  vertex parent  level\n");
        for (v = 0; v < G->nv; v++) printf("%6d%7d%7d\n", v, parent[v], level[v]);
    }
    printf("\n");
}



