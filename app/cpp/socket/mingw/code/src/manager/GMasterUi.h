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
    static GMasterUi* Create(const std::string& key);
    virtual void run(int _argc, char** _argv);
    static DWORD WINAPI onServer(LPVOID _params);
    static DWORD WINAPI onStart(LPVOID _params);
    static void onSignal(int _signal);
    void onMessage(std::queue<std::string>& _dataIn);

private:
    static sGMaster m_params;
};
//==============================================
#endif
//==============================================
