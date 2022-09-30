//===============================================
#ifndef _GConnection_
#define _GConnection_
//===============================================
#include "GObject2.h"
//===============================================
#define GCONNECT    GConnection::Instance()
//===============================================
class GConnection : public GObject2 {
public:
    GConnection();
    ~GConnection();

    static GConnection* Instance();

    void assign(const GConnection& _data);

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

    bool isConnect() const;

    void runConnection();
    void runDisconnection();

private:
    static GConnection* m_instance;
    int m_id;
    GString m_pseudo;
    GString m_password;
};
//==============================================
#endif
//==============================================
