//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess lProcess;
    lProcess.init();
    lProcess.run(_argc, _argv);
    lProcess.getLogs().print();
    lProcess.clean();
    return 0;
}
//===============================================
