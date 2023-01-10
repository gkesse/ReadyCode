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
    const GLog& getLogs() const;

protected:
    int main(const std::vector<std::string>& _args);

protected:
    GPoco* m_poco;
    GLog m_logs;
};
//==============================================
#endif
//==============================================
