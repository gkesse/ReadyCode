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
    GUser();
    GUser(const QString& _req);
    ~GUser();
    //
    void onModule(QString _req, GSocket* _client);
    void onSaveUser(QString _req, GSocket* _client);
};
//==============================================
#endif
//==============================================
