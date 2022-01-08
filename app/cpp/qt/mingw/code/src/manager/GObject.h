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
    std::string getDataPath() const;
    std::string getResourcePath(const std::string& _resource, const std::string& _filename) const;
    void showArgs(int _argc, char** _argv);
    //
    void initDom();
    void initDom(const std::string& _module, const std::string& _method);
    void loadDom(const std::string& _data);
    std::string getDom(const std::string& _encoding = "UTF-8", int _format = 4) const;
    void setModule(const std::string& _module);
    std::string getModule() const;
    void setMethod(const std::string& _method);
    std::string getMethod() const;

private:
    static GObject* m_instance;

protected:
    std::shared_ptr<GXml> m_dom;
};
//==============================================
#endif
//==============================================
