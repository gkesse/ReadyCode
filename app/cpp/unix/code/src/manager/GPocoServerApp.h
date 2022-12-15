//===============================================
#ifndef _GPocoServerApp_
#define _GPocoServerApp_
//===============================================
#include "GObject.h"
//===============================================
class GPocoServerApp : public Poco::Util::ServerApplication {
protected:
    int main(const std::vector<std::string>& _args);
};
//==============================================
#endif
//==============================================
