//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GPoco.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
    GPoco().initModule();
    GProcess lProcess;
    lProcess.initProcess();
    lProcess.run(_argc, _argv);
    lProcess.showErrors();
    GPoco().cleanModule();
    GXml().cleanModule();
    return 0;
}
//===============================================
