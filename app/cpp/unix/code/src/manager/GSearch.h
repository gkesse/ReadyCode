//===============================================
#ifndef _GSearch_
#define _GSearch_
//===============================================
#include "GManager.h"
//===============================================
class GSearch : public GManager {
public:
    GSearch();
    ~GSearch();
    GString serialize(const GString& _code = "search") const;
    bool deserialize(const GString& _data, const GString& _code = "search");

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
