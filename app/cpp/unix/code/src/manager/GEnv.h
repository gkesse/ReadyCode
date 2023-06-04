//===============================================
#ifndef _GEnv_
#define _GEnv_
//===============================================
#include "GInclude.h"
//===============================================
#define GENV    GEnv::Instance()
//===============================================
class GEnv {
public:
    GEnv();
    ~GEnv();
    static GEnv* Instance();
    void initEnv();
    bool isTestEnv() const;
    bool isProdEnv() const;
    GString getDataPath() const;
    GString getTmpDir() const;
    GString getEnv(const GString& _env, const GString& _defaultValue = "") const;

private:
    static GEnv* m_instance;
    GString m_envType;
    GString m_dataPath;
    GString m_tmpPath;
    bool m_isProdEnv;
    bool m_isTestEnv;
};
//==============================================
#endif
//==============================================
