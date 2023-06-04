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

    GString serialize(const GString& _code = "manager");
    void deserialize(const GString& _data, const GString& _code = "manager");

protected:
    GString m_moduleName;
    GString m_methodName;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
