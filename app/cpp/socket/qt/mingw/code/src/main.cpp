//===============================================
#include "GProcess.h"
#include "GQtLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess::Instance()->run(_argc, _argv);
    GQTLOG->showError();
    return 0;
}
//===============================================
