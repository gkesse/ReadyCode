//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GObject.h"
//===============================================
#define GMODULE_REQUIRED()  GERROR_ADD(eGERR, "Le module est obligatoire.")
#define GMODULE_UNKNOWN()   GERROR_ADD(eGERR, "Le module (%s) est inconnu.", m_module.c_str())
#define GMETHOD_REQUIRED()  GERROR_ADD(eGERR, "La méthode est obligatoire.")
#define GMETHOD_UNKNOWN()   GERROR_ADD(eGERR, "La méthode (%s : %s) est inconnue.", m_module.c_str(), m_method.c_str());
#define GDATA_EXIST()       GERROR_ADD(eGERR, "La donnée existe.");
#define GSAVE_OK()          GLOG_ADD(eGLOG,   "La donnée a bien été enregistrée.");
//===============================================
class GServer;
//===============================================
class GManager : public GObject {
public:
    GManager();
    GManager(const GManager& _manager);
    GManager(GManager* _manager);
    GManager(GServer* _server);
    virtual ~GManager();

    GObject* clone() const;

    void setManager(const GManager& _manager);
    void setManager(GManager* _manager);
    void setServer(GServer* _server);

    GString serialize(const GString& _code = "manager") const;
    bool deserialize(const GString& _data, const GString& _code = "manager");

    void setModule(const GString& _modules);
    void setMethod(const GString& _method);

    bool onModule();
    bool onConnection();
    bool onFile();
    bool onModules();
    bool onModulesData();

protected:
    GString m_module;
    GString m_method;
    GServer* m_server;
};
//==============================================
#endif
//==============================================
