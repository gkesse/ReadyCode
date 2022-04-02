//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
class GXml : public GObject {
public:
    GXml();
    virtual ~GXml();
    //
    void initModule();
    void cleanModule();
    //
    GXml& loadXmlFile(const std::string& _filename);
    GXml& loadXmlData(const std::string& _data);
    GXml& saveXmlFile(const std::string& _filename = "", const std::string& _encoding = "UTF-8", int _format = 4);
    //
    GXml& createDoc(const std::string& _version);
    GXml& createDoc(const std::string& _version, const std::string& _rootNode);
    GXml& createRoot(const std::string& _nodename);
    //
    GXml& getRoot(const std::string& _nodename);
    GXml& getNode(const std::string& _nodename);
    std::string getNodeValue() const;
    std::string getNodeValue(const std::string& _xpath);
    //
    GXml& createNode(const std::string& _nodename);
    GXml& createNodeValue(const std::string& _nodename, const std::string& _value);
    GXml& createNodePath(const std::string& _path, const std::string& _value = "");
    GXml& createCData(GXml& _xml, const std::string& _value);
    GXml& setNodeValue(const std::string& _value);
    GXml& setNodeValue(const std::string& _key, const std::string& _value);
    GXml& appendNode(GXml& _xml);
    GXml& appendNode(const std::string& _nodename);
    GXml& appendNode(const std::string& _nodename, const std::string& _value);
    GXml& appendNodeGet(const std::string& _nodename);
    GXml& appendNodeGet(const std::string& _nodename, const std::string& _value);
    GXml& appendCData(const std::string& _value);
    GXml& appendCData(const std::string& _nodename, const std::string& _value);
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
    //
    std::string getItem(const std::string& _code, const std::string& _data);

private:
    xmlNodePtr m_node;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
