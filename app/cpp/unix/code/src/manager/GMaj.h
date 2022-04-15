//===============================================
#ifndef _GMaj_
#define _GMaj_
//===============================================
#include "GObject.h"
//===============================================
class GMaj : public GObject {
public:
    GMaj();
    GMaj(const std::string& _filename);
    ~GMaj();
    void loadObj();
    void loadCode();
    void loadId();
    bool hasData() const;
    void insertData(const GMaj& _data);
    void updateData(const GMaj& _data);

private:
    int m_id;
    std::string m_code;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
