#include <xinu.h>

void deleteAllEdges(struct resourceGraph* graph, pid32 src) {
        struct node* curr = graph->adjList[src];
        struct node *temp;
        while (curr != NULL) {
                temp = curr->next;
                freemem(curr, sizeof(curr));
                curr = temp;
        }
        graph->adjList[src] = NULL;
}
