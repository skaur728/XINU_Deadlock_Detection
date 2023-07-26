#include <xinu.h>

int cycleFound = 0;
int detectCycle(struct resourceGraph* graph, pid32 src) {
        int32 i = graph->numNodes;
        int visited[i];
        int path[i];
        cycleDetectionHelper(graph, src, visited, path);
        if (cycleFound == 1) {
                return 1;
        } else {
                return 0;
        }
}

void cycleDetectionHelper(struct resourceGraph* graph, pid32 src, int visited[], int path[]) {
        visited[src] = 1;
        path[src] = 1;
        struct node* node = graph->adjList[src];
        while (node != NULL && !(isbadpid(node->pid)) ) {
                if (path[node->pid] == 1) {
                        cycleFound = 1;
                        return;
                } else if (visited[node->pid] == 0) {
                        cycleDetectionHelper(graph, node->pid, visited, path);
                }
                node = node->next;
        }
        path[src] = 0;
}
