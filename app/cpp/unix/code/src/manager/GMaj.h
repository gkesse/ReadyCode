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
    GMaj(const std::string& _path, const std::string& _filename);
    ~GMaj();
    //
    void onModule(GSocket* _client);
    void onUpdateDatabase(GSocket* _client);
    static void onUpdateDatabaseThread(GSocket* _client);
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
    void runMaj(const std::string& _filename, bool _isTestEnv);

private:
    int m_id;
    std::string m_code;
    std::string m_path;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
