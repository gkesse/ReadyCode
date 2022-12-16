//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GCurl.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GCurl().initCurl();
    GXml().initModule();
	GProcess().run(_argc, _argv);
    GERROR_SHOW(eGERR);
    GLOG_SHOW(eGERR);
	GXml().cleanModule();
	GCurl().cleanCurl();
	return 0;
}
//===============================================
