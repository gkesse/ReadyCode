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
    bool onNextCode(GSocket* _client);
    bool onUpdateCode(GSocket* _client);
    bool onDeleteCode(GSocket* _client);
    //
    bool createCode();
    bool searchCode();
    bool updateCode();
    bool deleteCode();
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
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
