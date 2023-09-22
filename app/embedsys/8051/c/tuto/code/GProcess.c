//===============================================
#include "GProcess.h"
#include "GSchRun.h"
//===============================================
static uchar gAction;
//===============================================
void GProcess_init() {
    gAction = 0;
    if(gAction == 0) GSchRun_init();
}
//===============================================
void GProcess_run() {
    if(gAction == 0) GSchRun_run();
}
//===============================================
