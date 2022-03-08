//===============================================
#include "GProcess.h"
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
	std::shared_ptr<GProcess> lProcess(new GProcess);
	lProcess->run(_argc, _argv);
	GLOG->showError();
	return 0;
}
//===============================================
