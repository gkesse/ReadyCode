//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    GDEFINE_OBJ(GProcess, lProcess)
    lProcess.run(&lProcess, _argc, _argv);
    lProcess.m_obj->m_logs->print(lProcess.m_obj->m_logs);
    return 0;
}
//===============================================
