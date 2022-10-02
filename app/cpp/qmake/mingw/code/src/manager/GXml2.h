//===============================================
#ifndef _GXml2_
#define _GXml2_
//===============================================
#include "GObject.h"
//===============================================
class GXml2 : public GObject {
public:
    GXml2();
    virtual ~GXml2();

    void release();

    void initModule();
    void cleanModule();

    bool loadXml(const GString& _xml);
    bool loadFile(const GString& _filename);
    bool loadNode(const GString& _data);

    bool createDoc();
    bool createNode(const GString& _name);
    bool createNodePath(const GString& _name);

    bool next();

    bool getNode(const GString& _path);
    GString getValue() const;

    bool setValue(const GString& _value, bool _isCData = false);

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
