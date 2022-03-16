//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GModule {
public:
    GMaster();
    GMaster(const QString& _req);
    ~GMaster();
    //
    void onModule(QString _req, GSocket* _client);
    //
    void onModuleUser(QString _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
