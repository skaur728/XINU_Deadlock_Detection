#include <xinu.h>

void addEdge(struct resourceGraph* graph, pid32 src, pid32 dest) {
        if (edgeExists(graph, src, dest) == 1 || src == dest) {
                return;
        }
        struct node* node = createNode(dest);
        node->next = graph->adjList[src];
        graph->adjList[src] = node;
}
