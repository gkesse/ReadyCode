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
    GManager(const GString& _code = "manager");
    ~GManager();

    GObject* clone() const;

    GString serialize(const GString& _code = "manager");
    bool deserialize(const GString& _data, const GString& _code = "manager");

    void setClient(GSocket* _client);
    void setModule(const GString& _module);
    void setMethod(const GString& _method);

protected:
    GString m_moduleName;
    GString m_methodName;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
