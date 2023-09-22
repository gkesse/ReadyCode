//===============================================
#include "GSchRun.h"
#include "GSch.h"
#include "GSchTask.h"
//===============================================
void GSchRun_init() {
    GSch_init(1);
    GSchTask_init();
    GSch_start();
}
//===============================================
void GSchRun_run() {
    GSch_dispatchTasks();
}
//===============================================
