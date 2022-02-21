//===============================================
#include "GProcess.h"
#include "GXml.h"
//===============================================
int main(int _argc, char** _argv) {
    GXml()->init(GXml());
    GProcess()->run(GProcess(), _argc, _argv);
    GProcess()->delete(GProcess());
    GXml()->clean(GXml());
    return 0;
}
//===============================================
