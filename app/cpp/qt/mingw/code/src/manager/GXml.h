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
    GXml& loadXmlFile(const std::string& _filename);
    GXml& getRoot(const std::string& _nodename);
    GXml& getNode(const std::string& _nodename);
    std::string getNodeValue() const;
    GXml& createXPath();
    GXml& queryXPath(const std::string& _query);
    int countXPath() const;
    GXml& getNodeXPath();
    GXml& getNodeItem(int _index);

private:
    xmlNodePtr m_node;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
};
//==============================================
#endif
//==============================================
