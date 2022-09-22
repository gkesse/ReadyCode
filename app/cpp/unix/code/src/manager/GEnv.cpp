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
    std::string lType = getEnvType();
    if(lType == "PROD") return true;
    return false;
}
//===============================================
bool GEnv::isTestEnv() const {
    if(isProdEnv()) return false;
    return true;
}
//===============================================
std::string GEnv::getEnvType() const {
    std::string lData = getEnv("GPROJECT_ENV");
    return lData;
}
//===============================================
std::string GEnv::getDataPath() const {
    std::string lData = getEnv("GPROJECT_DATA");
    return lData;
}
//===============================================
std::string GEnv::getTmpDir() const {
    std::string lData = getEnv("GPROJECT_TMP");
    return lData;
}
//===============================================
std::string GEnv::getEnv(const std::string& _env, const std::string& _defaultValue) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
