//===============================================
#ifndef _GPocoServerApp_
#define _GPocoServerApp_
//===============================================
#include "GObject.h"
//===============================================
class GPoco;
//===============================================
class GPocoServerApp : public Poco::Util::ServerApplication {
public:
    GPocoServerApp(GPoco* _poco);
    ~GPocoServerApp();

protected:
    int main(const std::vector<std::string>& _args);

private:
    GPoco* m_poco;

public:
    GLog m_logs;
};
//==============================================
#endif
//==============================================
