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

    void initModule();
    void cleanModule();

    bool loadXml(const GString2& _xml);
    bool loadFile(const GString2& _filename);

    bool createDoc();
    bool createNode(const GString2& _name);

    GString2 toString() const;

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
