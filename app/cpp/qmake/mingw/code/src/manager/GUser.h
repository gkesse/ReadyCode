//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GUser : public GModule {
public:
    GUser(QObject* _parent = 0);
    GUser(const QString& _req, QObject* _parent = 0);
    ~GUser();
    //
    void onModule(GSocket* _client);
    void onSaveUser(GSocket* _client);
};
//==============================================
#endif
//==============================================
