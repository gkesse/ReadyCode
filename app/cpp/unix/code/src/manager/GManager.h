//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GSearch.h"
//===============================================
class GSocket;
//===============================================
class GManager : public GSearch {
public:
    GManager();
    ~GManager();
    GObject* clone();
    //
    std::string serialize(const std::string& _code = "manager");
    void deserialize(const std::string& _data, const std::string& _code = "manager");
    //
    bool onModule(GSocket* _client);
    bool onCreateCode(GSocket* _client);
    bool onSearchCode(GSocket* _client);
    //
    bool createCode();
    bool searchCode();
    //
    bool loadId();
    bool loadLastId();
    bool loadDataCount();
    bool loadDataMap();
    //
    bool saveData();
    bool insertData();
    bool updateData();

private:
    int m_id;
    std::string m_code;
    std::string m_label;
};
//==============================================
#endif
//==============================================
