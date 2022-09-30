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
    virtual ~GXml();
    //
    void initModule();
    void cleanModule();
    //
    bool loadXml(const GString& _data);
    bool loadFile(const GString& _filename);
    bool loadNode(const GString& _data, bool _isRoot = true);
    bool saveXml(const GString& _filename = "", const GString& _encoding = "UTF-8", int _format = 4);
    bool isValidXml() const;
    //
    GString getNodeValue() const;
    //
    bool createDoc(const GString& _version = "1.0");
    bool createNode(const GString& _path);
    bool createXNode(const GString& _path, const GString& _value = "", bool _isCData = false);
    bool setNodeValue(const GString& _value, bool _isCData);
    //
    bool queryXPath(const GString& _path, bool _isRoot = true);
    bool getXPath(const GString& _path, bool _isRoot = true);
    int countXPath() const;
    bool getNodeXPath(int _index = 0);
    bool clearXNode();
    //
    bool setAttribute(const GString& _key, const GString& _value);
    //
    bool saveNode();
    bool restoreNode();
    //
    GString toString(const GString& _encoding = "UTF8", int _format = 4) const;
    GString toStringNode(const GString& _encoding = "UTF8", int _format = 4) const;

private:
    xmlNodePtr m_node;
    xmlNodePtr m_queryNode;
    std::stack<xmlNodePtr> m_nodeCopy;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    GString m_filename;
};
//==============================================
#endif
//==============================================
