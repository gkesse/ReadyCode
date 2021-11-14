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
    void runSocket(int argc, char** argv);
    void runOpenCV(int argc, char** argv);
    void runXml(int argc, char** argv);
    void runAsio(int argc, char** argv);
    void runCurl(int argc, char** argv);
    
private:
    static GProcess* m_instance;
};
//==============================================
#endif
//==============================================
