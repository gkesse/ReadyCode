//===============================================
#include "GEnv2.h"
#include "GLog2.h"
//===============================================
GEnv2::GEnv2()
: GObject2() {

}
//===============================================
GEnv2::~GEnv2() {

}
//===============================================
bool GEnv2::isProdEnv() const {
    GString2 lType = getEnvType();
    if(lType == "PROD") return true;
    return false;
}
//===============================================
bool GEnv2::isTestEnv() const {
    if(isProdEnv()) return false;
    return true;
}
//===============================================
GString2 GEnv2::getEnvType() const {
    GString2 lData = getEnv("GPROJECT_ENV");
    return lData;
}
//===============================================
GString2 GEnv2::getDataPath() const {
    GString2 lData = getEnv("GPROJECT_DATA");
    return lData;
}
//===============================================
GString2 GEnv2::getTmpDir() const {
    GString2 lData = getEnv("GPROJECT_TMP");
    return lData;
}
//===============================================   1
GString2 GEnv2::getEnv(const GString2& _env, const GString2& _defaultValue) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
