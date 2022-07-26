//===============================================
#ifndef _GUser_
#define _GUser_
//===============================================
#include "GModule.h"
//===============================================
class GUser : public GModule {
public:
    GUser(QObject* _parent = 0);
    ~GUser();
    QString serialize(const QString& _code = "user") const;
    void deserialize(const QString& _data, const QString& _code = "user");
    //
    void setId(int _id);
    void setPseudo(const QString& _pseudo);
    void setPassword(const QString& _password);
    //
    int getId() const;
    QString getPseudo() const;
    QString getPassword() const;
    //
    bool runConnection();
    bool createAccount();
    bool runDisconnection();
    //
    bool isConnect() const;

private:
    int m_id;
    QString m_pseudo;
    QString m_password;
    bool m_isConnect;
};
//==============================================
#endif
//==============================================
