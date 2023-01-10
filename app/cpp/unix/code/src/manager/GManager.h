//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GObject.h"
//===============================================
#define GMODULE_REQUIRED()  GERROR_ADD(eGERR, "Le module est obligatoire.")
#define GMODULE_UNKNOWN()   GERROR_ADD(eGERR, "Le module (%s) est inconnu.", m_moduleName.c_str())
#define GMETHOD_REQUIRED()  GERROR_ADD(eGERR, "La méthode est obligatoire.")
#define GMETHOD_UNKNOWN()   GERROR_ADD(eGERR, "La méthode (%s : %s) est inconnue.", m_moduleName.c_str(), m_methodName.c_str());
//===============================================
class GSocket;
//===============================================
class GManager : public GObject {
public:
    GManager();
    virtual ~GManager();

    GObject* clone() const;

    void setManager(const GManager& _manager);
    void setManager(GManager* _manager);
    void setServer(GSocket* _server);

    GString serialize(const GString& _code = "manager");
    void deserialize(const GString& _data, const GString& _code = "manager");

    void setModule(const GString& _modules);
    void setMethod(const GString& _method);
    bool isValid() const;

    bool onManager();
    bool onConnection();
    bool onFile();
    bool onModule();
    bool onModuleData();
    bool onModuleKey();
    bool onModuleMap();
    bool onModuleType();
    bool onQuery();
    bool onQueryType();

protected:
    GString m_moduleName;
    GString m_methodName;
    GSocket* m_server;
};
//==============================================
#endif
//==============================================
