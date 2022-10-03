//===============================================
#include "GEnv.h"
#include "GLog.h"
//===============================================
GEnv::GEnv()
: GObject() {
    initEnv();
}
//===============================================
GEnv::~GEnv() {

}
//===============================================
void GEnv::initEnv() {
    m_envType       = getEnv("GPROJECT_ENV");
    m_dataPath      = getEnv("GPROJECT_DATA");
    m_tmpPath       = getEnv("GPROJECT_TMP");
    m_isProdEnv     = (m_envType == "PROD");
    m_isTestEnv     = !m_isProdEnv;
}
//===============================================
bool GEnv::isTestEnv() const {
    return m_isTestEnv;
}
//===============================================
GString GEnv::getDataPath() const {
    return m_dataPath;
}
//===============================================
GString GEnv::getTmpDir() const {
    return m_tmpPath;
}
//===============================================   1
GString GEnv::getEnv(const GString& _env, const GString& _defaultValue) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
