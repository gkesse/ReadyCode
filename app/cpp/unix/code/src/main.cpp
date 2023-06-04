//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GPoco.h"
#include "GOpenSSL.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
    GPoco().initModule();
    GOpenSSL().initModule();
    GProcess lProcess;
    lProcess.run(_argc, _argv);
    lProcess.showErrors();
    GOpenSSL().clearModule();
    GPoco().cleanModule();
    GXml().cleanModule();
    return 0;
}
//===============================================
