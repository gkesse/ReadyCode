//===============================================
#ifndef _GSearch_
#define _GSearch_
//===============================================
#include "GManager.h"
//===============================================
class GSearch : public GManager {
public:
    GSearch(const GString& _code = "search");
    virtual ~GSearch();
    GString serialize(const GString& _code = "search") const;
    bool deserialize(const GString& _data, const GString& _code = "search");

    void setSearch(const GSearch& _search);

protected:
    int m_lastId;
    int m_dataCount;
    int m_dataSize;
    int m_dataOffset;
    bool m_hasData;
    GString m_where;
};
//==============================================
#endif
//==============================================
