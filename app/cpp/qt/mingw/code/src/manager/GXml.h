//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
#define GXML GXml::Instance()
//===============================================
class GXml : public GObject {
public:
    GXml();
    ~GXml();
    static GXml* Instance();
    //
    void initModule();
    void cleanModule();
    //
    GXml& loadXmlFile(const std::string& _filename);
    GXml& loadXmlData(const std::string& _data);
    GXml& saveXmlFile(const std::string& _filename = "", const std::string& _encoding = "UTF-8", int _format = 4);
    //
    GXml& createDoc(const std::string& _version);
    GXml& createRoot(const std::string& _nodename);
    //
    GXml& getRoot(const std::string& _nodename);
    //
    GXml& createNode(const std::string& _nodename);
    GXml& createCData(GXml& _xml, const std::string& _value);
    GXml& createNodeValue(const std::string& _nodename, const std::string& _value);
    GXml& setNodeValue(const std::string& _value);
    GXml& appendNode(GXml& _xml);
    GXml& appendNode(const std::string& _nodename);
    GXml& appendNode(const std::string& _nodename, const std::string& _value);
    GXml& appendCData(const std::string& _value);
    GXml& appendCData(const std::string& _nodename, const std::string& _value);
    GXml& replaceNode(GXml& _xml);
    //
    GXml& getNode(const std::string& _nodename);
    std::string getNodeValue() const;
    //
    GXml& createXPath();
    GXml& queryXPath(const std::string& _query);
    int countXPath() const;
    GXml& getNodeXPath();
    GXml& clearNodeXPath();
    GXml& getNodeItem(int _index);
    //
    std::string toString() const;
    std::string toString(const std::string& _encoding, int _format) const;

private:
    static GXml* m_instance;
    //
    xmlNodePtr m_node;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    //
    std::string m_filename;
};
//==============================================
#endif
//==============================================
