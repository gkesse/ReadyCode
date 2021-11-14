//===============================================
#ifndef _GOpenCVUi_
#define _GOpenCVUi_
//===============================================
#include "GInclude.h"
#include "GOpenCV.h"
//===============================================
class GOpenCVUi {
public:
    GOpenCVUi();
    virtual ~GOpenCVUi();
    static GOpenCVUi* Create(const std::string& key);
    virtual void run(int argc, char** argv);
    static void onTrackbar(int _pos, void* _params);

private:
    static GOpenCV lOpenCV;
    static sGParams lParams;
};
//==============================================
#endif
//==============================================
