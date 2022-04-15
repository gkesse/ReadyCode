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
    GMaj& loadObj();
    GMaj& saveObj();
    GMaj& loadCode();
    GMaj& loadId();
    bool hasData() const;
    GMaj& insertData();
    GMaj& updateData();

private:
    int m_id;
    std::string m_code;
    std::string m_filename;
};
//==============================================
#endif
//==============================================
