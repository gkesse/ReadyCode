//===============================================
#ifndef _GQtXml_
#define _GQtXml_
//===============================================
#include "GQtObject.h"
//===============================================
class GQtXml : public GQtObject {
    Q_OBJECT

public:
    GQtXml(QObject* _parent = 0);
    ~GQtXml();
    GQtXml& loadXmlFile(const QString& _filename);
    bool saveXmlFile(const QString& _filename = "", const QString& _encoding = "UTF-8", int _format = 4);
    //
    GQtXml& getRoot(const QString& _nodename);
    GQtXml& getNode(const QString& _nodename);
    QString getNodeValue() const;
    //
    GQtXml& createNode(const QString& _nodename);
    GQtXml& createNodeValue(const QString& _nodename, const QString& _value);
    GQtXml& setNodeValue(const QString& _value);
    GQtXml& appendNode(GQtXml& _xml);
    GQtXml& replaceNode(GQtXml& _xml);
    //
    GQtXml& createXPath();
    GQtXml& queryXPath(const QString& _query);
    int countXPath() const;
    GQtXml& getNodeXPath();
    GQtXml& getNodeItem(int _index);
    GQtXml& clearNodeXPath();
    //
    GQtXml& createNodeCData(GQtXml& _xml, const QString& _value);
    GQtXml& createNodeCData(const QString& _nodename, const QString& _value);
    GQtXml& setNodeCData(const QString& _value);
    QString getNodeCData() const;

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
