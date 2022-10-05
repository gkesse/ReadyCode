//===============================================
#ifndef _GSearch_
#define _GSearch_
//===============================================
#include "GModule.h"
//===============================================
class GSearch : public GModule {
public:
    GSearch();
    ~GSearch();
    GString serialize(const GString& _code = "search");
    bool deserialize(const GString& _data, const GString& _code = "search");

protected:
    int m_lastId;
    int m_dataCount;
    int m_dataSize;
    int m_dataOffset;
    GString m_where;
};
//==============================================
#endif
//==============================================
