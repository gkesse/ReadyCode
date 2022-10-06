//===============================================
#ifndef _GModule_
#define _GModule_
//===============================================
#include "GObject.h"
//===============================================
#define GMODULE_REQUIRED()  GERROR_ADD(eGERR, "Le module est obligatoire.")
#define GMODULE_UNKNOWN()   GERROR_ADD(eGERR, "Le module (%s) est inconnu.", m_modules.c_str())
#define GMETHOD_REQUIRED()  GERROR_ADD(eGERR, "La méthode est obligatoire.")
#define GMETHOD_UNKNOWN()   GERROR_ADD(eGERR, "La méthode (%s : %s) est inconnue.", m_modules.c_str(), m_method.c_str());
//===============================================
class GServer;
//===============================================
class GModule : public GObject {
public:
    GModule();
    GModule(const GModule& _modules);
    GModule(GModule* _modules);
    GModule(GServer* _server);
    virtual ~GModule();

    GObject* clone() const;

    void setModule(const GModule& _modules);
    void setModule(GModule* _modules);
    void setServer(GServer* _server);

    GString serialize(const GString& _code = "request") const;
    bool deserialize(const GString& _data, const GString& _code = "request");

    void setModule(const GString& _modules);
    void setMethod(const GString& _method);

    bool onModule();
    bool onConnection();
    bool onFile();
    bool onModules();
    bool onModulesData();

protected:
    GString m_modules;
    GString m_method;
    GServer* m_server;
};
//==============================================
#endif
//==============================================
