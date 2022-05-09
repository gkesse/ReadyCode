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
    std::string getEnvType() const;
    std::string getDataPath() const;
    std::string getTmpDir() const;
    std::string getEnv(const std::string& _env, const std::string& _defaultValue = "") const;
};
//==============================================
#endif
//==============================================
