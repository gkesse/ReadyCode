//===============================================
#include "GEnv.h"
#include "GLog.h"
//===============================================
GEnv::GEnv(QObject* _parent) : GObject(_parent) {

}
//===============================================
GEnv::~GEnv() {

}
//===============================================
bool GEnv::isProdEnv() const {
    QString lType = getEnvType();
    if(lType == "PROD") return true;
    return false;
}
//===============================================
bool GEnv::isTestEnv() const {
    if(isProdEnv()) return false;
    return true;
}
//===============================================
QString GEnv::getEnvType() const {
    QString lData = getEnv("GPROJECT_ENV");
    return lData;
}
//===============================================
QString GEnv::getDataPath() const {
    QString lData = getEnv("GPROJECT_DATA");
    return lData;
}
//===============================================
QString GEnv::getTmpDir() const {
    QString lData = getEnv("GPROJECT_TMP");
    return lData;
}
//===============================================
QString GEnv::getEnv(const QString& _env, const QString& _defaultValue) const {
    QString lEnv = QString :: fromLocal8Bit(qgetenv(_env.toStdString().c_str()));
    if(lEnv == "") return _defaultValue;
    return lEnv;
}
//===============================================
