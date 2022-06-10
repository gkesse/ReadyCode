//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
class GString;
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
    bool loadXml(const std::string& _data);
    bool loadFile(const std::string& _filename);
    GXml& loadNode(const std::string& _data, bool _isRoot = true);
    bool saveXml(const std::string& _filename = "", const std::string& _encoding = "UTF-8", int _format = 4);
    bool isValidXml() const;
    //
    std::string getNodeValue() const;
    //
    bool createDoc(const std::string& _version = "1.0");
    bool createNode(const std::string& _path);
    bool createXNode(const std::string& _path, const std::string& _value = "", bool _isCData = false);
    bool setNodeValue(const std::string& _value, bool _isCData);
    //
    bool queryXPath(const std::string& _path, bool _isRoot = true);
    bool getXPath(const std::string& _path, bool _isRoot = true);
    int countXPath() const;
    bool getNodeXPath(int _index = 0);
    bool clearXNode();
    //
    bool setAttribute(const std::string& _key, const std::string& _value);
    //
    bool saveNode();
    bool restoreNode();
    //
    std::string toString(const std::string& _encoding = "UTF8", int _format = 4) const;
    std::string toStringNode(const std::string& _encoding = "UTF8", int _format = 4) const;

private:
    xmlNodePtr m_node;
    xmlNodePtr m_queryNode;
    std::stack<xmlNodePtr> m_nodeCopy;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
