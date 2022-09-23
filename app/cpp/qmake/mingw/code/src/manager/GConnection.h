//===============================================
#ifndef _GConnection_
#define _GConnection_
//===============================================
#include "GModule2.h"
//===============================================
class GConnection : public GModule2 {
public:
    GConnection(QObject* _parent = 0);
    ~GConnection();
    GString serialize(const GString& _code = "connection") const;
    bool deserialize(const GString& _data, const GString& _code = "connection");
    //
    void setId(int _id);
    void setPseudo(const GString& _pseudo);
    void setPassword(const GString& _password);
    //
    int getId() const;
    GString getPseudo() const;
    GString getPassword() const;
    //
    bool runConnection();
    bool createAccount();
    bool runDisconnection();
    //
    bool isConnect() const;

private:
    int m_id;
    GString m_pseudo;
    GString m_password;
    bool m_isConnect;
};
//==============================================
#endif
//==============================================
