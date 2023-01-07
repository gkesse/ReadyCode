//===============================================
#include "GEnv.h"
//===============================================
GEnv::GEnv() {
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
    m_isTestEnv     = (m_envType == "TEST");
    m_isProdEnv     = !m_isTestEnv;
}
//===============================================
bool GEnv::isTestEnv() const {
    return m_isTestEnv;
}
//===============================================
bool GEnv::isProdEnv() const {
    return m_isProdEnv;
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
