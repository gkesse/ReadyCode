//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess* lProcess = GProcess_new();
    lProcess->run(lProcess, _argc, _argv);
    lProcess->delete(lProcess);
    return 0;
}
//===============================================
