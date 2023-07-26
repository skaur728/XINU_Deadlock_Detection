#include <xinu.h>

sid32 sem;
sid32 sem2;
void test2(sid32 sem1, sid32 sem2) {
        wait(sem2);
        //kprintf("process two obtained sem 2\n");
        //sleepms(100);
        //wait(sem);
        //kprintf("process two obtained sem 1\n");
        sleep(2000);
}
