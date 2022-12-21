//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GCurl.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
    GCurl().initCurl();
	GProcess().run(_argc, _argv);
    GERROR_SHOW(eGERR);
    GLOG_SHOW(eGERR);
	GCurl().cleanCurl();
    GXml().cleanModule();
	return 0;
}
//===============================================
