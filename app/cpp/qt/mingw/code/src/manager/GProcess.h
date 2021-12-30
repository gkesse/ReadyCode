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
    void createDom();
    std::string getName() const;
    void runDefault(int _argc, char** _argv);
    void runQt(int _argc, char** _argv);
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
