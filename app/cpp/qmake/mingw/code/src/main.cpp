//===============================================
#include "GProcess.h"
#include "GXml.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
	QSharedPointer<GXml> lXml(new GXml);
	lXml->initModule();
	QSharedPointer<GProcess> lProcess(new GProcess);
	lProcess->run(_argc, _argv);
	GLOGI->showError(0);
	lXml->cleanModule();
	return 0;
}
//===============================================
