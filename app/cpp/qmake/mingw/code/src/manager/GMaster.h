//===============================================
#ifndef _GMaster_
#define _GMaster_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMaster : public GModule {
    Q_OBJECT

public:
    GMaster(QObject* _parent = 0);
    GMaster(const QString& _req, QObject* _parent = 0);
    ~GMaster();
    //
    void onModule(GSocket* _client);
    //
    void onModuleTest(GSocket* _client);
    void onModuleUser(GSocket* _client);
};
//==============================================
#endif
//==============================================
