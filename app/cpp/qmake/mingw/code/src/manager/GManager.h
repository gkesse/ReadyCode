//===============================================
#ifndef _GModule_
#define _GModule_
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

    GString serialize(const GString& _code = "request") const;
    bool deserialize(const GString& _data, const GString& _code = "request");

    void setClient(GSocket* _client);
    void setModule(const GString& _modules);
    void setMethod(const GString& _method);

protected:
    GString m_modules;
    GString m_method;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
