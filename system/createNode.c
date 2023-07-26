#include <xinu.h>

struct node* createNode(pid32 pid) {
        struct node* node = (struct node*)getmem(sizeof(struct node)); 
        node->pid = pid;
        node->next = NULL;
        return node;
}
