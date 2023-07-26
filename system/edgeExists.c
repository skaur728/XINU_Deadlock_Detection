#include <xinu.h>

int edgeExists(struct resourceGraph* graph, pid32 src, pid32 dest) {
        struct node* node = graph->adjList[src];
        while (node != NULL) {
                if (node->pid == dest) {
                        return 1;
                }
                node = node->next;
        }
        return 0;
}
