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
    bool openFileRD(const QString _filename);
    GQtXml& getRoot(const QString& _nodeName);
    GQtXml& getNode(const QString& _nodeName);
    int getNodeCount(const QString& _nodeName) const;
    GQtXml& getNodeItem(const QString& _nodeName, int _index);
    QString getNodeValue() const;

private:
    QDomDocument m_dom;
    QDomElement m_node;
};
//==============================================
#endif
//==============================================
