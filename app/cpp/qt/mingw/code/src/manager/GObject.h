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
    std::string getDataPath() const;
    std::string getResourcePath(const std::string& _resource, const std::string& _filename) const;
    void showArgs(int _argc, char** _argv);
    //
    void initDom();
    void loadDom(const std::string& _data);
    //
    void createResult();
    void addResultMsg(const std::string& _msg);
    //
    void createError();
    void addErrorMsg(const std::string& _msg);
    int countErrors() const;
    bool hasErrors() const;
    std::string getErrors(int _index) const;
    //
    void createRequest(const std::string& _module, const std::string& _method);
    std::string getModule() const;
    std::string getMethod() const;
    std::string getRequestName() const;
    //
    static void onUnknownModule(GObject* _request, GSocket* _client);
    void onUnknownMethod(GObject* _request, GSocket* _client);
    //
    std::string toString() const;
    std::string toString(const std::string& _encoding, int _format) const;
    //
    std::string sformat(const char* _format, ...) const;

private:
    static GObject* m_instance;

protected:
    std::shared_ptr<GXml> m_dom;
    std::shared_ptr<GXml> m_domData;
    //
    static std::shared_ptr<GObject> m_requestDom;
    static std::shared_ptr<GObject> m_resultOkDom;
    //
    GObject* m_request;
    GSocket* m_client;
};
//==============================================
#endif
//==============================================
