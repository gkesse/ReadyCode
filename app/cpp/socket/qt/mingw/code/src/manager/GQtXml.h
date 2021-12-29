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
    GQtXml(GQtXml* _xml, QObject* _parent = 0);
    ~GQtXml();
    bool openFileRD(const QString _filename);
    bool saveFile(const QString _filename = "");
    GQtXml& getRoot(const QString& _nodeName);
    GQtXml& getNode(const QString& _nodeName);
    GQtXml& getNodeOrEmpty(const QString& _nodeName);
    int countNode(const QString& _nodeName) const;
    GQtXml& clearNode(const QString& _nodeName);
    bool hasNode(const QString& _nodeName);
    GQtXml& appendNode(GQtXml& _node);
    GQtXml& setNodeValue(const QString& _value);
    GQtXml& createNode(const QString& _nodeName);
    GQtXml& createNodeText(const QString& _nodeName, const QString& _text);
    GQtXml& createText(const QString& _text);
    GQtXml& appendText(const QString& _text);
    GQtXml& getNodeItem(const QString& _nodeName, int _index);
    QString getNodeValue() const;
    QString getNodeValueOrEmpty() const;

private:
    GQtXml* m_xml;
    QDomDocument m_dom;
    QDomElement m_node;
    QString m_filename;
};
//==============================================
#endif
//==============================================
