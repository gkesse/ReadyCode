//===============================================
#ifndef _GMaj_
#define _GMaj_
//===============================================
#include "GModule.h"
//===============================================
class GSocket;
//===============================================
class GMaj : public GModule {
public:
    GMaj();
    GMaj(const GString& _path, const GString& _filename);
    ~GMaj();
    static GMaj* Instance();
    //
    GString serialize(const GString& _code = "maj") const;
    void deserialize(const GString& _req, const GString& _code = "maj");
    //
    void onModule(GSocket* _client);
    void onUpdateDatabase(GSocket* _client);
    static void onUpdateDatabaseThread(void* _params);
    //
    void createDB();
    void createDB(bool _isTestEnv);
    void loadCode();
    void loadId();
    void loadId(bool _isTestEnv);
    void saveData();
    void saveData(bool _isTestEnv);
    void insertData(bool _isTestEnv);
    void updateData(bool _isTestEnv);
    void runMaj();
    void runMaj(bool _isTestEnv);
    void runMaj(const GString& _filename, bool _isTestEnv);

private:
    int m_id;
    GString m_code;
    GString m_path;
    GString m_filename;
};
//==============================================
#endif
//==============================================
