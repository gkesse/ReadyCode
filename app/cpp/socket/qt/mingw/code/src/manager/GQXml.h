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
    void fileRead(const QString& _filename);
    void fileWrite(const QString& _filename);
    void content();
    void root(GQXml& _root);
    void tagName(QString& _tagName);
    bool attribute(const QString& _attribute);
    void attribute(const QString& _attribute, QString& _value);
    void firstChild(GQXml& _xml, const QString& _tagName = "");
    void nextSibling(GQXml& _xml, const QString& _tagName = "");
    void text(QString& _text);
    void text(GQXml& _xml, QString& _text);
    bool isNull();
    void save(int _indent);
    void element(GQXml& _xml, const QString& _element);
    void close();

protected:
    QDomDocument m_document;
    QDomElement m_element;
    QDomText m_text;
    QFile m_file;
};
//==============================================
#endif
//==============================================
