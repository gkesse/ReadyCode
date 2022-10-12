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
    GManager(const GString& _codeName = "manager");
    ~GManager();

    GObject* clone() const;

    GString serialize() const;
    bool deserialize(const GString& _data);

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
