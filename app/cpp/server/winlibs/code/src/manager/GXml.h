//===============================================
#ifndef _GXml_
#define _GXml_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GXml {
public:
    GXml();
    ~GXml();
    void createDoc();
    xmlNodePtr addObj(const GString& _name);
    void addData(const GString& _name, const GString& _value);
    GString toString() const;

protected:
    xmlDocPtr m_doc;
    xmlNodePtr m_node;
};
//===============================================
#endif
//===============================================
