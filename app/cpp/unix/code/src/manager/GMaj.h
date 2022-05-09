//===============================================
#ifndef _GMaj_
#define _GMaj_
//===============================================
#include "GObject.h"
//===============================================
class GMaj : public GObject {
public:
    GMaj();
    GMaj(const std::string& _path, const std::string& _filename);
    ~GMaj();
    void createDB();
    void loadCode();
    void loadId();
    void loadId(bool _isTestEnv);
    void saveData();
    void saveData(bool _isTestEnv);
    void insertData(bool _isTestEnv);
    void updateData(bool _isTestEnv);
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
