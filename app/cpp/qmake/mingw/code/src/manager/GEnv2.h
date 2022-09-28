//===============================================
#ifndef _GEnv2_
#define _GEnv2_
//===============================================
#include "GObject2.h"
//===============================================
class GEnv2 : public GObject2 {
public:
    GEnv2();
    ~GEnv2();
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
