//===============================================
#include "GProcess.h"
#include "GXml.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcess* lProcess = GProcess_new();
    GXml* lXml = GXml_new();

    lXml->init(lXml);
    lProcess->run(lProcess, _argc, _argv);
    lXml->clean(lXml);

    lXml->delete(lXml);
    lProcess->delete(lProcess);
    return 0;
}
//===============================================
