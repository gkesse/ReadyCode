//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess* lProcess = GProcess_new();
    lProcess->init(lProcess);
    lProcess->run(lProcess, _argc, _argv);
    lProcess->clean(lProcess);
    lProcess->delete(lProcess);
    return 0;
}
//===============================================
