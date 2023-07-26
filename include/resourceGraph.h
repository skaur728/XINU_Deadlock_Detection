
struct node {
        pid32 pid;
        struct node* next;
};
struct resourceGraph {
        int numNodes;
        struct node** adjList;
};

struct resourceGraph* systemGraph;
