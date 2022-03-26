//===============================================
#include "GEnv.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GEnv::GEnv() : GObject() {

}
//===============================================
GEnv::~GEnv() {

}
//===============================================
std::string GEnv::getEnv(const std::string& _env, const std::string& _defaultValue) {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return _defaultValue;
    return lEnv;
}
//===============================================
