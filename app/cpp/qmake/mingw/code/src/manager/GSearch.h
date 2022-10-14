//===============================================
#ifndef _GSearch_
#define _GSearch_
//===============================================
#include "GManager.h"
//===============================================
#define GSEARCH_AVOID()     GERROR_ADD(eGERR, "Aucun résultat n'a été trouvé.")
//===============================================
class GSearch : public GManager {
public:
    GSearch(const GString& _code = "search");
    ~GSearch();
    GString serialize(const GString& _code = "search") const;
    bool deserialize(const GString& _data, const GString& _code = "search");
    void setSearch(const GSearch& _search);
    virtual void onNextData();
    bool hasData() const;

protected:
    int m_lastId;
    int m_dataCount;
    int m_dataSize;
    int m_dataOffset;
    bool m_hasData;
};
//==============================================
#endif
//==============================================
