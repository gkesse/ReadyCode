//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    GProcessI()->run(GProcessI(), _argc, _argv);
    GProcessI()->delete(GProcessI());
    return 0;
}
//===============================================
