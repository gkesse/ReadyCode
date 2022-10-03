//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GObject.h"
//===============================================
#define GMODULE_REQUIRED()  GERROR_ADD(eGERR, "La module est obligatoire.")
#define GMODULE_UNKNOWN()   GERROR_ADD(eGERR, "Le module (%s) est inconnu.", m_module.c_str())
#define GMETHOD_REQUIRED()  GERROR_ADD(eGERR, "La méthode est obligatoire.")
#define GMETHOD_UNKNOWN()   GERROR_ADD(eGERR, "La méthode (%s:%s) est inconnu.", m_module.c_str(), m_method.c_str());
//===============================================
class GServer;
//===============================================
class GModule : public GObject {
public:
    GModule();
    GModule(const GModule& _module);
    GModule(GModule* _module);
    GModule(GServer* _server);
    virtual ~GModule();

    GObject* clone() const;

    void assign(const GModule& _module);
    void assign(GModule* _module);
    void assign(GServer* _server);

    GString serialize(const GString& _code = "request") const;
    bool deserialize(const GString& _data, const GString& _code = "request");

    void setModule(const GString& _module);
    void setMethod(const GString& _method);

    bool onModule();
    bool onConnection();
    bool onFile();
    bool onModules();

protected:
    GString m_module;
    GString m_method;
    GServer* m_server;
};
//==============================================
#endif
//==============================================
