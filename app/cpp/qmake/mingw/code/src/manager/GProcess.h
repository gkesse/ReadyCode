//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
class GProcess : public GObject {
	Q_OBJECT

public:
	GProcess(QObject* _parent = 0);
	~GProcess();
	void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runTest(int _argc, char** _argv);
    void runPad(int _argc, char** _argv);
    void runPadMdi(int _argc, char** _argv);
    void runMainPad(int _argc, char** _argv);
};
//===============================================
#endif
//===============================================
