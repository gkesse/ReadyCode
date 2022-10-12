//===============================================
#ifndef _GSearch_
#define _GSearch_
//===============================================
#include "GManager.h"
//===============================================
class GSearch : public GManager {
public:
    GSearch(const GString& _codeName = "search");
    ~GSearch();
    GString serialize() const;
    bool deserialize(const GString& _data);

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
