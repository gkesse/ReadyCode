//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GInclude.h"
//===============================================
class GXml {
public:
    GXml();
    virtual ~GXml();

    void release();

    void initModule();
    void cleanModule();

    bool loadXml(const GString& _xml);
    bool loadFile(const GString& _filename);
    bool loadNode(const GString& _data);

    bool createDoc();
    bool createNode(const GString& _name);
    bool createXNode(const GString& _name);

    bool next();

    bool getXNode(const GString& _path);
    GString getValue() const;

    bool setValue(const GString& _value, bool _isCData = false);
    bool replaceNode(GXml& _dom);

    int countNode(const GString& _path);

    GString toString() const;
    GString toNode() const;

    void print() const;

private:
    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
    xmlNodePtr m_node;
    xmlNodePtr m_next;
};
//==============================================
#endif
//==============================================
