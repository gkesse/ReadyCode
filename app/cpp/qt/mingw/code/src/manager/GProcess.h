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
    void runSQLite(int _argc, char** _argv);
    void createDom();
    std::string getName() const;
    bool getProcShow() const;
    bool getArgShow() const;
    static DWORD WINAPI onServerTcp(LPVOID _params);

private:
    static GProcess* m_instance;
};
//==============================================
#endif
//==============================================
