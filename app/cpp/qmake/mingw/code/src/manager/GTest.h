//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GObject.h"
//===============================================
class GTest : public GObject {
	Q_OBJECT

public:
	GTest(QObject* _parent = 0);
	~GTest();
	void run(int _argc, char** _argv);
	void runTest(int _argc, char** _argv);
    void runPath(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runSocketServer(int _argc, char** _argv);
    void runSocketClient(int _argc, char** _argv);
    void runSocketServerWrite(int _argc, char** _argv);
    void runSocketClientWrite(int _argc, char** _argv);
    void runThread(int _argc, char** _argv);
    static DWORD WINAPI onThread(LPVOID _params);
    void runTimer(int _argc, char** _argv);
    static VOID CALLBACK onTimer(HWND, UINT, UINT_PTR, DWORD);
};
//===============================================
#endif
//===============================================
