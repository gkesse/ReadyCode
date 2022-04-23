//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GObject.h"
//===============================================
#define GUSERI  GUser::Instance()
//===============================================
class GUser : public GObject {
public:
    GUser(QObject* _parent = 0);
    ~GUser();
    static GUser* Instance();
    //
    QString getPseudo() const;
    //
    bool hasUser(const QString& _username) const;
    bool hasUser(const QString& _username, const QString& _password) const;

private:
    static GUser* m_instance;
    QString m_pseudo;
};
//==============================================
#endif
//==============================================
