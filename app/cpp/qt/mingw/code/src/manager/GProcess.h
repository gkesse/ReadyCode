//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GObject.h"
//===============================================
class GProcess : public GObject {
private:
    GProcess();
    
public:
    ~GProcess();
    static GProcess* Instance();
    void run(int _argc, char** _argv);
    void runStudio(int _argc, char** _argv);
    void runSpreadsheet(int _argc, char** _argv);
    void runSocket(int _argc, char** _argv);
    void runMaster(int _argc, char** _argv);
    void runSQLite(int _argc, char** _argv);
    void runTimer(int _argc, char** _argv);
    void createDoms();
    std::string getName(int _argc, char** _argv) const;
    std::string getName() const;
    bool getNameUse() const;
    bool getProcShow() const;
    bool getArgShow() const;
    static DWORD WINAPI onServerTcp(LPVOID _params);
    static void CALLBACK onServerTcpTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);

private:
    static GProcess* m_instance;
};
//==============================================
#endif
//==============================================
