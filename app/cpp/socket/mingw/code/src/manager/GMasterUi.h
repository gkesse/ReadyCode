//===============================================
#ifndef _GMasterUi_
#define _GMasterUi_
//===============================================
#include "GInclude.h"
//===============================================
struct sGMaster;
//===============================================
class GMasterUi {
public:
    GMasterUi();
    virtual ~GMasterUi();
    static GMasterUi* Create(const std::string& _key);
    virtual void run(int _argc, char** _argv);
    static DWORD WINAPI onServer(LPVOID _params);
    static DWORD WINAPI onStart(LPVOID _params);
    static void onSignal(int _signal);
    void onMessage(std::queue<std::string>& _dataIn);
    void onSQLite(const std::string& _method, const std::string& _dataIn);
    void onOpenCV(const std::string& _method, const std::string& _dataIn);
    void onOpenGL(const std::string& _method, const std::string& _dataIn);

private:
    static sGMaster m_params;
};
//==============================================
#endif
//==============================================
