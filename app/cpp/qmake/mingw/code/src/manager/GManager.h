//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GObject.h"
//===============================================
class GSocket;
//===============================================
class GManager : public GObject {
public:
    GManager();
    ~GManager();

    GObject* clone() const;

    GString serialize(const GString& _code = "manager") const;
    bool deserialize(const GString& _data, const GString& _code = "manager");

    void setClient(GSocket* _client);
    void setModule(const GString& _module);
    void setMethod(const GString& _method);

protected:
    GString m_module;
    GString m_method;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
