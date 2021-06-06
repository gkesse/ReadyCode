//===============================================
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
//===============================================
static void* onTask(void* params) {
    char* lName = (char*)params;
    pid_t lPid = getppid();
    for(int i = 0; i < 5; i++) {
        printf("on execute le thread %s avec le pid %d\n", lName, lPid);
        sleep(1);
    }
    return 0;
}
//===============================================
int main(int argc, char** argv) {
    pthread_t  lThreadA;
    pthread_t  lThreadB;
    pthread_create(&lThreadA, NULL, onTask, "A");
    pthread_create(&lThreadB, NULL, onTask, "B");
    pthread_join(lThreadA, NULL);
    pthread_join(lThreadB, NULL);
    return 0;
}
//===============================================
