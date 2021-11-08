//===============================================
#ifndef _GQXml_
#define _GQXml_
//===============================================
#include "GInclude.h"
//===============================================
class GQXml {
public:
    GQXml();
    ~GQXml();
    void load(const QString& _filename);
    void save(const QString& _filename, int _indent);
    void root(GQXml& _root);
    void tagName(QString& _tagName);
    bool attribute(const QString& _attribute);
    void attribute(const QString& _attribute, QString& _value);
    void firstChild(GQXml& _xml, const QString& _tagName = "");
    void nextSibling(GQXml& _xml, const QString& _tagName = "");
    void text(QString& _text);
    void appendChild(const GQXml& _chlid);
    void replaceChild(const GQXml& _old, const GQXml& _new);
    bool isNull();
    void element(GQXml& _xml, const QString& _element);

protected:
    QDomDocument m_document;
    QDomElement m_element;
    QDomText m_text;
};
//==============================================
#endif
//==============================================
