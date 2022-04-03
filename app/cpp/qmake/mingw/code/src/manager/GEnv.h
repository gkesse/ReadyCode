//===============================================
#ifndef _GEnv_
#define _GEnv_
//===============================================
#include "GObject.h"
//===============================================
class GEnv : public GObject {
    Q_OBJECT

public:
    GEnv(QObject* _parent = 0);
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
