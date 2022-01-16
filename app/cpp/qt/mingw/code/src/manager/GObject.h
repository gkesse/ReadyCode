//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
#define GOBJECT GObject::Instance()
#define GRES(x, y) GOBJECT->getResourcePath(x, y)
//===============================================
class GXml;
class GSocket;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    static GObject* Instance();
    //
    virtual std::string getDataPath() const;
    virtual std::string getResourcePath(const std::string& _resource, const std::string& _filename) const;
    virtual void showArgs(int _argc, char** _argv);
    //
    virtual void initDom();
    virtual void loadDom(const std::string& _data);
    //
    virtual void createResult();
    virtual void addResultMsg(const std::string& _msg);
    //
    virtual void createError();
    virtual void addErrorMsg(const std::string& _msg);
    virtual int countErrors() const;
    virtual bool hasErrors() const;
    virtual std::string getErrors(int _index) const;
    //
    virtual void createRequest(const std::string& _module, const std::string& _method);
    virtual std::string getModule() const;
    virtual std::string getMethod() const;
    virtual std::string getRequestName() const;
    //
    static void onUnknownModule(const std::string& _request, GSocket* _client);
    static void onUnknownMethod(const std::string& _request, GSocket* _client);
    //
    virtual std::string toString(const std::string& _encoding = "UTF-8", int _format = 4) const;
    //
    virtual std::string sformat(const char* _format, ...) const;

private:
    static GObject* m_instance;

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GXml> m_domData;
    //
    std::string m_request;
    GSocket* m_client;
};
//==============================================
#endif
//==============================================
