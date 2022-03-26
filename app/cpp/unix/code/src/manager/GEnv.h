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
    std::string getEnv(const std::string& _env, const std::string& _defaultValue = "");
};
//==============================================
#endif
//==============================================