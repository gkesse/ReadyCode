//===============================================
#ifndef _GConnection_
#define _GConnection_
//===============================================
#include "GObject.h"
//===============================================
#define GCONNECT    GConnection::Instance()
//===============================================
class GConnection : public GObject {
public:
    GConnection();
    ~GConnection();

    static GConnection* Instance();

    void assign(const GConnection& _data);

    GString serialize() const;
    void deserialize(const GString& _data);
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
