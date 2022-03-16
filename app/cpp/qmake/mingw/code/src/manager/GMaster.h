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
    void onModule(QString _req, GSocket* _client);
    //
    void onModuleUser(QString _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
