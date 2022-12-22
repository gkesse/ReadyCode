//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GCurl.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
    GCurl().initModule();
	GProcess().run(_argc, _argv);
    GERROR_SHOW(eGERR);
    GLOG_SHOW(eGERR);
	GCurl().cleanModule();
    GXml().cleanModule();
	return 0;
}
//===============================================
