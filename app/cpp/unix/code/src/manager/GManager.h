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
    //
    std::string serialize(const std::string& _code = "manager") const;
    void deserialize(const std::string& _data, const std::string& _code = "manager");
    //
    bool onModule(GSocket* _client);
    void onCreateCode(GSocket* _client);
    //
    bool createCode();
    //
    bool loadCodeId();
    bool loadCode();
    bool saveCode();
    bool insertCode();
    bool updateCode();

private:
    int m_id;
    std::string m_code;
    std::string m_label;
};
//==============================================
#endif
//==============================================
