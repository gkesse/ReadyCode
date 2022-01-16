//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GObject.h"
//===============================================
#define GREQUEST GRequest::Instance()
//===============================================
class GXml;
//===============================================
class GRequest : public GObject {
public:
    GRequest();
    ~GRequest();
    static GRequest* Instance();
    //
    void createRequest();
    void addRequest(GXml& _dom);
    void addRequest(const std::string& _dom);
    //
    std::vector<std::string> loadXmlModules() const;
    std::vector<GRequest> loadRequests(const std::string& _module) const;
    GRequest loadRequests(const std::string& _module, int _index) const;
    int countXmlMessages() const;
    int countXmlMessages(const std::string& _module) const;
    std::string getXmlId(const std::string& _module, int _index) const;
    std::string getXmlName(const std::string& _module, int _index) const;
    std::string getXmlName(int _index) const;
    std::string getXmlMessage(const std::string& _module, int _index) const;
    //
    std::string getId() const;
    std::string getModule() const;
    std::string getMethod() const;
    std::string getMessage() const;
    //
    void setId(const std::string& _id);
    void setModule(const std::string& _module);
    void setMethod(const std::string& _method);
    void setMessage(const std::string& _message);


private:
    static GRequest* m_instance;
    //
    std::string m_id;
    std::string m_module;
    std::string m_method;
    std::string m_message;
};
//==============================================
#endif
//==============================================
