//===============================================
#include "GEnv2.h"
#include "GLog2.h"
//===============================================
GEnv2::GEnv2(QObject* _parent)
: GObject2(_parent) {

}
//===============================================
GEnv2::~GEnv2() {

}
//===============================================
bool GEnv2::isProdEnv() const {
    GString lType = getEnvType();
    if(lType == "PROD") return true;
    return false;
}
//===============================================
bool GEnv2::isTestEnv() const {
    if(isProdEnv()) return false;
    return true;
}
//===============================================
GString GEnv2::getEnvType() const {
    GString lData = getEnv("GPROJECT_ENV");
    return lData;
}
//===============================================
GString GEnv2::getDataPath() const {
    GString lData = getEnv("GPROJECT_DATA");
    return lData;
}
//===============================================
GString GEnv2::getTmpDir() const {
    GString lData = getEnv("GPROJECT_TMP");
    return lData;
}
//===============================================
GString GEnv2::getEnv(const GString& _env, const GString& _defaultValue) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
