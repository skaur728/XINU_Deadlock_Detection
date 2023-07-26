/* wait.c - wait */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wait  -  Cause current process to wait on a semaphore
 *------------------------------------------------------------------------
 */
syscall	wait(
                sid32		sem		/* Semaphore on which to wait  */
            )
{
        intmask mask;			/* Saved interrupt mask		*/
        struct	procent *prptr;		/* Ptr to process's table entry	*/
        struct	sentry *semptr;		/* Ptr to sempahore table entry	*/

        mask = disable();
        if (isbadsem(sem)) {
                restore(mask);
                return SYSERR;
        }

        semptr = &semtab[sem];
        if (semptr->sstate == S_FREE) {
                restore(mask);
                return SYSERR;
        }
        //kprintf("pid %d\n", currpid);
        if (--(semptr->scount) < 0) {		/* If caller must block	*/
                //kprintf("sem %d\n", sem);
                if (currpid != 0) {
                        //kprintf("blocking pid %d\n", currpid);
                }
                prptr = &proctab[currpid];
                prptr->prstate = PR_WAIT;	/* Set state to waiting	*/
                prptr->prsem = sem;		/* Record semaphore ID	*/
                enqueue(currpid,semptr->squeue);/* Enqueue on semaphore	*/
                qid16 queue = semptr->squeue;
                qid16 tail = queuetail(queue);
                qid16 head = queuehead(queue);
                pid32 p = firstid(queue);
                if (currpid != 0) {
                        while (p != tail && !(isbadpid(p)) && p != 0) {
                                addEdge(systemGraph,currpid, p);
                                int test = detectCycle(systemGraph, currpid);
                                if (test == 1) {
                                        kprintf("Deadlock detected aborting process\n");
                                        restore(mask);
                                        return SYSERR;
                                }
                                p = queuetab[p].qnext;
                        }
                        pid32* arr = semptr->owners;
                        int32 i;
                        for (i = 0; i < semptr->ownerSize; i++) {
                                addEdge(systemGraph, currpid, *arr);
                                int test = detectCycle(systemGraph, currpid);
                                if (test == 1) {
                                        kprintf("Deadlock detected aborting process\n");
                                        restore(mask);
                                        return SYSERR;
                                }
                                arr++;
                        }
                }
                resched();			/*   and reschedule	*/
        } else {
                pid32* arr = semptr->owners;
                arr[semptr->ownerSize] = currpid;
                semptr->ownerSize += 1;
        }

        restore(mask);
        return OK;
}
