//===============================================
#include "GProcess.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess::Instance()->run(_argc, _argv);
    GLOG->showError();
    return 0;
}
//===============================================
