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

protected:
    GString m_moduleName;
    GString m_methodName;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
