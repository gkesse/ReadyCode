//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GObject.h"
//===============================================
class GUser : public GObject {
public:
    GUser(QObject* _parent = 0);
    ~GUser();
    //
    bool existUsername(const QString& _username) const;
};
//==============================================
#endif
//==============================================
