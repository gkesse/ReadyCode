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
    GString getEnvType() const;
    GString getDataPath() const;
    GString getTmpDir() const;
    GString getEnv(const GString& _env, const GString& _defaultValue = "") const;
};
//==============================================
#endif
//==============================================
