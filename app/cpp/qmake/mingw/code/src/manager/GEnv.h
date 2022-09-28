//===============================================
#ifndef _GEnv_
#define _GEnv_
//===============================================
#include "GObject.h"
//===============================================
class GEnv : public GObject {
public:
    GEnv();
    ~GEnv();
    bool isProdEnv() const;
    bool isTestEnv() const;
    QString getEnvType() const;
    QString getDataPath() const;
    QString getTmpDir() const;
    QString getEnv(const QString& _env, const QString& _defaultValue = "") const;
};
//==============================================
#endif
//==============================================
