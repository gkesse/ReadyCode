//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GObject.h"
//===============================================
class GXml : public GObject {
    Q_OBJECT

public:
    GXml(QObject* _parent = 0);
    ~GXml();
    //
    void initModule();
    void cleanModule();
    //
    GXml& loadXmlFile(const QString& _filename);
    GXml& loadXmlData(const QString& _data);
    GXml& saveXmlFile(const QString& _filename = "", const QString& _encoding = "UTF-8", int _format = 4);
    //
    GXml& createDoc(const QString& _version);
    GXml& createRoot(const QString& _nodename);
    GXml& createRequest(const QString& _module, const QString& _method);
    //
    GXml& getRoot(const QString& _nodename);
    GXml& getNode(const QString& _nodename);
    QString getNodeValue() const;
    QString getNodeValue(const QString& _xpath);
    //
    GXml& createNode(const QString& _nodename);
    GXml& createNodeValue(const QString& _nodename, const QString& _value);
    GXml& createNodePath(const QString& _path, const QString& _value = "");
    GXml& setNodeValue(const QString& _value);
    GXml& appendNode(GXml& _xml);
    GXml& replaceNode(GXml& _xml);
    //
    GXml& createXPath();
    GXml& createXPath(const QString& _data);
    GXml& queryXPath(const QString& _query);
    int countXPath() const;
    GXml& getNodeXPath();
    GXml& getNodeItem(int _index);
    GXml& clearNodeXPath();
    //
    GXml& createNodeCData(GXml& _xml, const QString& _value);
    GXml& createNodeCData(const QString& _nodename, const QString& _value);
    GXml& setNodeCData(const QString& _value);
    QString getNodeCData() const;
    //
    QString toString(const QString& _encoding = "UTF8", int _format = 4) const;

private:
    xmlNodePtr m_node;
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    QString m_filename;
};
//==============================================
#endif
//==============================================
