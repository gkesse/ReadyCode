//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GInclude.h"
//===============================================
class GXml {
public:
    GXml();
    ~GXml();
    void load(const QString& _filename);
    void save(const QString& _filename, int _indent);
    void content(const QString& _content);
    void toString(QString& _content);
    void toText(QString& _content);
    void value(const QString& _value);
    void root(GXml& _root);
    void tagName(QString& _tagName);
    bool attribute(const QString& _attribute);
    void attribute(const QString& _attribute, QString& _value);
    void attributes(const QString& _attribute, const QString& _value);
    void firstChild(GXml& _xml, const QString& _tagName = "");
    void nextSibling(GXml& _xml, const QString& _tagName = "");
    void previousSibling(GXml& _xml, const QString& _tagName = "");
    void text(QString& _text);
    void text(GXml& _xml, const QString& _text);
    void appendChild(const GXml& _chlid);
    void replaceChild(const GXml& _old, const GXml& _new);
    bool isNull();
    void element(GXml& _xml, const QString& _name);
    void elements(GXml& _xml, const QString& _name);
    void element(GXml& _xml, int _index);

protected:
    QDomDocument m_document;
    QDomElement m_element;
    QDomText m_text;
    QDomNodeList m_nodes;
};
//==============================================
#endif
//==============================================
