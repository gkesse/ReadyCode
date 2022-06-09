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
    bool createXNode(const std::string& _path, const std::string& _value = "", bool _isCData = false, bool _isGet = true);
    bool createRNode(const std::string& _path, const std::string& _value = "", bool _isCData = false);
    bool setNodeValue(const std::string& _value, bool _isCData);
    bool appendNode(const std::string& _nodename, const std::string& _value = "", bool _isCData = false);
    GXml& replaceNode(GXml& _xml);
    //
    bool queryXPath(const std::string& _path, bool _isRoot = true);
    void getXPath(const std::string& _path, bool _isRoot = true);
    int countXPath() const;
    bool getNodeXPath(int _index = 0);
    GXml& clearNodeXPath();
    //
    GXml& setAttribute(const std::string& _key, const std::string& _value);
    //
    void saveNode();
    void restoreNode();
    //
    std::string toString(const std::string& _encoding = "UTF8", int _format = 4) const;
    std::string toStringNode(const std::string& _encoding = "UTF8", int _format = 4) const;

private:
    xmlNodePtr m_node;
    std::stack<xmlNodePtr> m_nodeCopy;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
