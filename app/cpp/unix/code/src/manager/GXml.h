//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
class GXml : public GObject {
public:
    GXml();
    GXml(const std::string& _data, bool _isFile);
    GXml(const std::string& _version, const std::string& _nodeRoot);
    virtual ~GXml();
    //
    void initModule();
    void cleanModule();
    //
    void loadXml();
    void loadXml(const std::string& _data, bool _isFile);
    GXml& loadXmlData(const std::string& _data);
    GXml& loadNodeData(const std::string& _data, bool _isRoot = true);
    GXml& saveXmlFile(const std::string& _filename = "", const std::string& _encoding = "UTF-8", int _format = 4);
    bool isValidXml() const;
    //
    GXml& createDoc();
    GXml& createRoot();
    //
    GXml& getRoot();
    GXml& getNode(const std::string& _nodename);
    std::string getNodeValue() const;
    std::string getNodeValue(const std::string& _xpath);
    //
    void createXNode(const std::string& _path);
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
    GXml& setNodeCData(const std::string& _key, const std::string& _value);
    std::string getNodeCData() const;
    //
    GXml& setAttribute(const std::string& _key, const std::string& _value);
    //
    std::string toString(const std::string& _encoding = "UTF8", int _format = 4) const;
    std::string toStringNode(const std::string& _encoding = "UTF8", int _format = 4) const;

private:
    xmlNodePtr m_node;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    std::string m_data;
    bool m_isFile;
    std::string m_version;
    std::string m_nodeRoot;
};
//==============================================
#endif
//==============================================
