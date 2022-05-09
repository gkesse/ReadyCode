//===============================================
#ifndef _GQtXml2_
#define _GQtXml2_
//===============================================
#include "GQtObject.h"
//===============================================
class GQtXml2 : public GQtObject {
    Q_OBJECT

public:
    GQtXml2(QObject* _parent = 0);
    GQtXml2(GQtXml2* _xml, QObject* _parent = 0);
    ~GQtXml2();
    bool loadXmlFile(const QString _filename);
    bool saveXmlFile(const QString _filename = "");
    GQtXml2& getRoot(const QString& _nodeName);
    GQtXml2& getNode(const QString& _nodeName);
    GQtXml2& getNodeOrEmpty(const QString& _nodeName);
    int countNode(const QString& _nodeName) const;
    GQtXml2& clearNode(const QString& _nodeName);
    bool hasNode(const QString& _nodeName);
    GQtXml2& appendNode(GQtXml2& _node);
    GQtXml2& setNodeValue(const QString& _value);
    GQtXml2& createNode(const QString& _nodeName);
    GQtXml2& createNodeText(const QString& _nodeName, const QString& _text);
    GQtXml2& createText(const QString& _text);
    GQtXml2& appendText(const QString& _text);
    GQtXml2& getNodeItem(const QString& _nodeName, int _index);
    QString getNodeValue() const;
    QString getCData() const;
    QString getNodeValueOrEmpty() const;

private:
    GQtXml2* m_xml;
    QDomDocument m_dom;
    QDomElement m_node;
    QString m_filename;
};
//==============================================
#endif
//==============================================
