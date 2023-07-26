#include <xinu.h>

struct resourceGraph* createGraph(int nodes) {
        struct resourceGraph* graph = (struct resourceGraph*)getmem(sizeof(struct resourceGraph));
        graph->numNodes = nodes;
        graph->adjList = (struct node**)getmem(nodes * sizeof(struct node*));
        int32 i;
        for (i = 0; i < nodes; i++) {
                graph->adjList[i] = NULL;
        }
        return graph;
}
