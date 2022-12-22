//===============================================
#ifndef _GEnv_
#define _GEnv_
//===============================================
#include "GObject.h"
//===============================================
class GEnv : public GObject {
public:
    GEnv(const GString& _codeName = "envs");
    ~GEnv();
    void initEnv();
    bool isTestEnv() const;
    GString getDataPath() const;
    GString getTmpDir() const;
    GString getEnv(const GString& _env, const GString& _defaultValue = "") const;

private:
    GString m_envType;
    GString m_dataPath;
    GString m_tmpPath;
    bool m_isProdEnv;
    bool m_isTestEnv;
};
//==============================================
#endif
//==============================================
