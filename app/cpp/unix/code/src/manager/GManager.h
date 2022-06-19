//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GManager : public GModule {
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
    bool loadCodeId();
    bool loadCode();
    bool loadCodeMap();
    //
    bool saveCode();
    bool insertCode();
    bool updateCode();

private:
    int m_id;
    std::string m_code;
    std::string m_label;
    std::string m_where;
    std::string m_orderBy;
};
//==============================================
#endif
//==============================================
