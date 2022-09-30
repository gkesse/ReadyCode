//===============================================
#include "GEnv.h"
#include "GLog.h"
//===============================================
GEnv::GEnv() : GObject() {

}
//===============================================
GEnv::~GEnv() {

}
//===============================================
bool GEnv::isProdEnv() const {
    GString lType = getEnvType();
    if(lType == "PROD") return true;
    return false;
}
//===============================================
bool GEnv::isTestEnv() const {
    if(isProdEnv()) return false;
    return true;
}
//===============================================
GString GEnv::getEnvType() const {
    GString lData = getEnv("GPROJECT_ENV");
    return lData;
}
//===============================================
GString GEnv::getDataPath() const {
    GString lData = getEnv("GPROJECT_DATA");
    return lData;
}
//===============================================
GString GEnv::getTmpDir() const {
    GString lData = getEnv("GPROJECT_TMP");
    return lData;
}
//===============================================
GString GEnv::getEnv(const GString& _env, const GString& _defaultValue) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
