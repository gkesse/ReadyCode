//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
class GXml : public GObject {
public:
    GXml();
    ~GXml();
    //
    void initModule();
    void cleanModule();
    //
    GXml& loadXmlFile(const std::string& _filename);
    bool saveXmlFile(const std::string& _filename = "", const std::string& _encoding = "UTF-8", int _format = 4);
    //
    GXml& createDoc(const std::string& _version);
    GXml& createRoot(const std::string& _nodename);
    GXml& createRequest(const std::string& _module, const std::string& _method);
    //
    GXml& getRoot(const std::string& _nodename);
    GXml& getNode(const std::string& _nodename);
    std::string getNodeValue() const;
    //
    GXml& createNode(const std::string& _nodename);
    GXml& createNodePath(const std::string& _path, const std::string& _value = "");
    GXml& createNodeFromString(const std::string& _value);
    GXml& createNodeValue(const std::string& _nodename, const std::string& _value);
    GXml& setNodeValue(const std::string& _value);
    GXml& appendNode(GXml& _xml);
    GXml& replaceNode(GXml& _xml);
    //
    GXml& createXPath();
    GXml& queryXPath(const std::string& _query);
    int countXPath() const;
    GXml& getNodeXPath();
    GXml& getNodeItem(int _index);
    GXml& clearNodeXPath();
    //
    GXml& createNodeCData(GXml& _xml, const std::string& _value);
    GXml& createNodeCData(const std::string& _nodename, const std::string& _value);
    GXml& setNodeCData(const std::string& _value);
    std::string getNodeCData() const;
    //
    std::string toString(const std::string& _encoding = "UTF8", int _format = 4) const;

private:
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
