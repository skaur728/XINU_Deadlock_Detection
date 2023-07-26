# Xinu_Deadlock_Detection
## Description
### This project implements deadlock detection in Xinu, by creating a custom graph data structure that represents all the current processes. Each node in the graph represents a process. The detection algorithm utilizes depth-first search (DFS) to find cycles in the graph, identifying deadlock scenarios. Once a deadlock is detected, the system aborts the process that caused the deadlock and returns a system error, preventing further disruptions in the system's operation.

## Files Changed Under include/
### resourceGraph.h 
#### Includes the definition of the graph data structure consisting of a number of nodes and corresponding adjacency lists. It also includes the definition for the node data structure including its process pid and next pointer in the adjacency list. Declares a global system graph variable that will represent the graph for all of the processes in the system.
### semaphore.h
#### Added two new fields: owners and ownerSize. These correspond to the current processes that currently own/have a hold of the semaphore. OwnerSize corresponds to the amount of such processes.

## Files Changed Under system/
### addEdge.c
#### Adds an edge to the system by updating the adjacency list for the source node. Prevents adding existing edges or edges with the same source and destination node.
### createGraph.c
#### Creates a graph with the number of nodes specified as a parameter. 
### createNode.c
#### Creates a node with the pid specified as a parameter.
### deleteAllEdges.c
#### Deletes all of the edges from a source node in a graph; both graph and source node are specified as parameters. Deletes all nodes in adjacency list.
### deleteOwner.c
#### Removes the specified process as an owner of the specified semaphore; both process and semaphore are specified as parameters. 
### detectCycle.c
#### Detects a cycle in the specified graph as a parameter. Uses a recursive helper function to keep track of all visited nodes and nodes in current path being checked. If a node is reached twice in the current path, there is a cycle.
### edgeExists.c
#### Checks if the specified edge exists in the graph.
### initialize.c
#### Added the initialization of the system graph which has NPROC number of nodes to denote the number of nodes cannot exceed the total number of processes in the system.
### semcreate.c
#### Added the allocation of memory for the possible owners of the semaphore. Initialized the owner size to 0.
### signal.c
#### Added the step to delete all the edges corresponding to the process node who is making the signal call. Added the step to delete the current process as an owner of the semaphore.
### wait.c
#### Adds edges from the current calling process to the rest of the processes waiting on the semaphore and any processes that currently own the semaphore. Checks if a cycle exists upon each addition and terminates the process if so. If the process must not block it is simply added as an owner. 
