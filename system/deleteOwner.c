#include <xinu.h>

void deleteOwner(struct sentry *semptr, pid32 pid) {
        int32 index = 0;
        pid32* arr = semptr->owners;
        int32 i;
        if (semptr->ownerSize == 1) {
                semptr->owners[0] = NULL;
                semptr->ownerSize -= 1;
                return;
        }
        for (i = 0; i < semptr->ownerSize; i++) {
                if (*arr == pid) {
                        index = i;
                        break;
                }
        }
        for (i = index; i < semptr->ownerSize-1; i++) {
                semptr->owners[i] = semptr->owners[i+1];
        }
        semptr->ownerSize -= 1;
}
