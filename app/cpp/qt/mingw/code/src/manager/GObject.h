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
//===============================================
class GObject {
public:
    GObject();
    ~GObject();
    static GObject* Instance();
    //
    std::string getDataPath() const;
    std::string getResourcePath(const std::string& _resource, const std::string& _filename) const;
    void showArgs(int _argc, char** _argv);
    //
    void initDom();
    void initDom(const std::string& _module, const std::string& _method);
    void initResult();
    void initResultOk();
    void initError();
    void loadDom(const std::string& _data);
    //
    void addResult();
    void addResult(const std::string& _msg);
    void addError();
    void addError(const std::string& _msg);
    void addModule(const std::string& _module);
    void addMethod(const std::string& _method);
    //
    std::string toString(const std::string& _encoding = "UTF-8", int _format = 4) const;
    //
    std::string getModule() const;
    std::string getMethod() const;
    std::string getResultOk() const;
    // erros
    int countErrors() const;
    bool hasErrors() const;
    std::string getErrors(int _index) const;

private:
    static GObject* m_instance;

protected:
    static const int FORMAT_SIZE = 1024;

protected:
    std::shared_ptr<GXml> m_dom;
    char m_format[FORMAT_SIZE + 1];
};
//==============================================
#endif
//==============================================
