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
    std::string serialize(const std::string& _code = "search");
    void deserialize(const std::string& _data, const std::string& _code = "search");

protected:
    int m_lastId;
    int m_dataCount;
    int m_dataSize;
    int m_dataOffset;
    std::string m_where;
};
//==============================================
#endif
//==============================================
