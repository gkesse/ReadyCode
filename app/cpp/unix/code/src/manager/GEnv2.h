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
    GString2 getEnvType() const;
    GString2 getDataPath() const;
    GString2 getTmpDir() const;
    GString2 getEnv(const GString2& _env, const GString2& _defaultValue = "") const;
};
//==============================================
#endif
//==============================================
