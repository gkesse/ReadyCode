//===============================================
#include "GProcess.h"
#include "GLog.h"
#include "GXml.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml lXml;
    lXml.initModule();
    GProcess lProcess;
    lProcess.run(_argc, _argv);
    GLOGI->showError();
    lXml.cleanModule();
    return 0;
}
//===============================================
