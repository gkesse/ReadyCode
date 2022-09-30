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
    GString serialize(const GString& _code = "manager");
    void deserialize(const GString& _data, const GString& _code = "manager");
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
    GString m_code;
    GString m_label;
    std::vector<GObject*> m_map;
};
//==============================================
#endif
//==============================================
