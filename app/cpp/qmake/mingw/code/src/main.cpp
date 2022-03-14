//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml lXml;
	lXml.initModule();
	GProcess lProcess;
	lProcess.run(_argc, _argv);
	GLOGI->showError(0);
	lXml.cleanModule();
	return 0;
}
//===============================================
