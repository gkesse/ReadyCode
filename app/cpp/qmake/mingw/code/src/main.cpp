//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml().initModule();
	GProcess().run(_argc, _argv);
	GERROR_SHOW(eGERR);
	GXml().cleanModule();
	return 0;
}
//===============================================
