//===============================================
#ifndef _GCss_
#define _GCss_
//===============================================
#include "GSearch.h"
//===============================================
class GTableWidgetUi;
//===============================================
class GCss : public GSearch {
public:
    GCss(const GString& _code = "css");
    ~GCss();
    GObject* clone() const;
    GString serialize(const GString& _code = "css");
    bool deserialize(const GString& _data, const GString& _code = "css");

    void setKey(const GString& _key);
    void setFilename(const GString& _filename);
    GString getKey() const;
    GString getFilename() const;

    void saveCss();

protected:
    int m_id;
    GString m_key;
    GString m_filename;
    std::vector<GObject*> m_map;
    std::shared_ptr<GTableWidgetUi> m_tableWidget;
};
//==============================================
#endif
//==============================================
