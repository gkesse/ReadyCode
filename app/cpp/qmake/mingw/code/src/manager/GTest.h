//===============================================
#ifndef _GTest_
#define _GTest_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GTest : public GModule {
	Q_OBJECT

public:
	GTest(QObject* _parent = 0);
	GTest(const QString& _req, QObject* _parent = 0);
	~GTest();
	void run(int _argc, char** _argv);
	void runTest(int _argc, char** _argv);
    void runPath(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runSocketServer(int _argc, char** _argv);
    void runSocketClient(int _argc, char** _argv);
    void runSocketServerWrite(int _argc, char** _argv);
    void runSocketClientWrite(int _argc, char** _argv);
    void runSocketServerStart(int _argc, char** _argv);
    static DWORD WINAPI onSocketServerStartThread(LPVOID _params);
    static VOID CALLBACK onSocketServerStartTimer(HWND, UINT, UINT_PTR, DWORD);
    void runSocketClientStart(int _argc, char** _argv);
    void runThread(int _argc, char** _argv);
    static DWORD WINAPI onThread(LPVOID _params);
    void runTimer(int _argc, char** _argv);
    static VOID CALLBACK onTimer(HWND, UINT, UINT_PTR, DWORD);
    void runRequest(int _argc, char** _argv);
    void runRequestSend(int _argc, char** _argv);
    void runRequestSaveUser(int _argc, char** _argv);
    void runRequestGetUser(int _argc, char** _argv);
    void runRequestError(int _argc, char** _argv);
    void runResponse(int _argc, char** _argv);
    //
    void onModule(QString _req, GSocket* _client);
    void onRequestSaveUser(QString _req, GSocket* _client);
    void onRequestGetUser(QString _req, GSocket* _client);
    void onRequestError(QString _req, GSocket* _client);

private:
    static GTest* m_test;
    GSocket* m_server;
};
//===============================================
#endif
//===============================================
