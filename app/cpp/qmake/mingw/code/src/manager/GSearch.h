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
    GString serialize(const GString& _code = "search");
    void deserialize(const GString& _data, const GString& _code = "search");

    void setSearch(const GSearch& _search);
    void setSearch(GSearch* _search);
    void setSearch(const std::shared_ptr<GSearch>& _search);

    void setDataSize(int _dataSize);
    bool hasData() const;

    virtual void onNextData();
    virtual void onAddData();
    virtual void onMoveUpData();
    virtual void onMoveDownData();

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
