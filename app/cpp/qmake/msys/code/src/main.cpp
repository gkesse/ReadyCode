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
	GLOG->showError();
	lXml->cleanModule();
	return 0;
}
//===============================================
