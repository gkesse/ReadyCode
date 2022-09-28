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
    bool loadXml(const QString& _data);
    bool loadFile(const QString& _filename);
    bool loadNode(const QString& _data, const QString& _encoding = "UTF-8");
    bool saveXml(const QString& _filename = "", const QString& _encoding = "UTF-8", int _format = 4);
    bool isValidXml() const;
    //
    QString getNodeValue() const;
    //
    bool createDoc(const QString& _version = "1.0");
    bool createNode(const QString& _path);
    bool createXNode(const QString& _path, const QString& _value = "", bool _isCData = false);
    bool setNodeValue(const QString& _value, bool _isCData);
    //
    bool queryXPath(const QString& _path, bool _isRoot = true);
    bool getXPath(const QString& _path, bool _isRoot = true);
    int countXPath() const;
    bool getNodeXPath(int _index = 0);
    bool clearXNode();
    //
    bool setAttribute(const QString& _key, const QString& _value);
    //
    bool saveNode();
    bool restoreNode();
    xmlChar* convertData(const char* _data, const char* _encoding = "UTF-8");
    //
    QString toString(const QString& _encoding = "UTF-8", int _format = 4) const;
    QString toStringNode(const QString& _encoding = "UTF-8", int _format = 4) const;

private:
    xmlNodePtr m_node;
    xmlNodePtr m_queryNode;
    QStack<xmlNodePtr> m_nodeCopy;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    QString m_filename;
};
//==============================================
#endif
//==============================================
