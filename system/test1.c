#include <xinu.h>

sid32 sem;
sid32 sem2;
void test1() {
        wait(sem);
        //kprintf("process one obtained sem 1\n");
        sleepms(100);
        wait(sem2);
        //kprintf("process one obtained sem 2\n");
        //sleep(1000);
}
