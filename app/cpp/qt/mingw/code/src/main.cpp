//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GQtLog.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXML->initModule();
    GPROCESS->run(_argc, _argv);
    GQTLOG->showError();
    GERROR->showErrors();
    GXML->cleanModule();
    return 0;
}
//===============================================
