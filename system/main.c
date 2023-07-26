/*  main.c  - main */

#include <xinu.h>

sid32 sem;
sid32 sem2;
sid32 sem_resource1;
sid32 sem_resource2;
void process1();
void process2();
void process1()
{
    wait(sem_resource1);  // Wait for resource 1
    kprintf("Process 1: Acquired resource 1\n");
    sleepms(100);         // Simulate some work

    wait(sem_resource2);  // Wait for resource 2
    kprintf("Process 1: Acquired resource 2\n");

    // Critical section
    kprintf("Process 1: Inside critical section\n");

    signal(sem_resource2);  // Release resource 2
    signal(sem_resource1);  // Release resource 1
}

void process2()
{
    wait(sem_resource2);  // Wait for resource 2
    kprintf("Process 2: Acquired resource 2\n");
    sleepms(100);         // Simulate some work

    wait(sem_resource1);  // Wait for resource 1
    kprintf("Process 2: Acquired resource 1\n");

    // Critical section
    kprintf("Process 2: Inside critical section\n");

    signal(sem_resource1);  // Release resource 1
    signal(sem_resource2);  // Release resource 2
}
process	main(void)
{
    
        sem_resource1 = semcreate(1);
        sem_resource2 = semcreate(1);

        //kprintf("sem1 %d sem2 %d\n", sem_resource1, sem_resource2);
        //pid32 procOne = create(test1,128, 30,"test", sem, sem2, CONSOLE); 
        resume(create(process1,128, 30,"test", 0)); 
        resume(create(process2,128, 30,"test", 0)); 
        //pid32 procTwo = create(test2,128, 30,"test", sem, sem2, CONSOLE); 
        //resume(procOne);
        //resume(procTwo);
        //kprintf("proc one %d proc two %d\n", procOne, procTwo);
	return OK;
    
}

