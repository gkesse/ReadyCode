//===============================================
#include "GProcess.h"
#include "GLog.h"
#include "GXml.h"
//===============================================
int main(int _argc, char** _argv) {
	std::shared_ptr<GXml> lXml(new GXml);
	lXml->initModule();
	std::shared_ptr<GProcess> lProcess(new GProcess);
	lProcess->run(_argc, _argv);
	GLOG->showError();
	lXml->cleanModule();
	return 0;
}
//===============================================
