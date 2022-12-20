//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GCurl.h"
#include "GOpenSSL.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
    GCurl().initCurl();
    GOpenSSL().initModule();
	GProcess().run(_argc, _argv);
    GERROR_SHOW(eGERR);
    GLOG_SHOW(eGERR);
    GOpenSSL().clearModule();
	GCurl().cleanCurl();
    GXml().cleanModule();
	return 0;
}
//===============================================
