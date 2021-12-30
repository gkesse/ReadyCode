//===============================================
#include "GProcess.h"
#include "GQtLog.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess::Instance()->run(_argc, _argv);
    GQTLOG->showError();
    GLOG->showError();
    return 0;
}
//===============================================
