//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GInclude.h"
//===============================================
class GProcess {
private:
    GProcess();
    
public:
    ~GProcess();
    static GProcess* Instance();
    void run(int _argc, char** _argv);
    void runDefault(int _argc, char** _argv);
    void runQt(int _argc, char** _argv);
    void runXml(int _argc, char** _argv);
    void runSocket(int _argc, char** _argv);
    void runSQLite(int _argc, char** _argv);
    void runFile(int _argc, char** _argv);
    void runStudio(int _argc, char** _argv);
    
private:
    static GProcess* m_instance;
};
//==============================================
#endif
//==============================================
