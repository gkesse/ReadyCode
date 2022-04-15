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
    bool hasData() const;
    void saveData();
    void insertData();
    void updateData();
    void runMaj();
    void runMaj(const std::string& _filename);

private:
    int m_id;
    std::string m_code;
    std::string m_path;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
