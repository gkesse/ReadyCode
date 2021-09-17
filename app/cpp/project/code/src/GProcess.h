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
    void run(int argc, char** argv);
    void runDefault(int argc, char** argv);
    void runPro(int argc, char** argv);
    
private:
    static GProcess* m_instance;
};
//==============================================
#endif
//==============================================
