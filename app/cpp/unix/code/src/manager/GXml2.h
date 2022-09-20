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

    void setData(const GString2& _data);
    void setFilename(const GString2& _filename);
    void setPath(const GString2& _path);

    bool loadData();
    bool loadFile();
    GString2 getData();

private:
    GString2 m_data;
    GString2 m_filename;
    GString2 m_path;

    xmlDocPtr m_doc;
    xmlXPathContextPtr m_xpath;
    xmlXPathObjectPtr m_xpathObj;
};
//==============================================
#endif
//==============================================
