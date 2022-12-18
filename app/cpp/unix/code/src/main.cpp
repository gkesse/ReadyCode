//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GPoco.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
    GPoco().initModule();
    GProcess().run(_argc, _argv);
    GLOGI->showErrors();
    GPoco().cleanModule();
    GXml().cleanModule();
    return 0;
}
//===============================================
