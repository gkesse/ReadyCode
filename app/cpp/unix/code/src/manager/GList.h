//===============================================
#ifndef _GList_
#define _GList_
//===============================================
#include "GObject.h"
//===============================================
class GList : public std::vector<GString> {
public:
    GList();
    ~GList();
    GString toSqlArrayString() const;
    GString toSqlArrayInt() const;
};
//==============================================
#endif
//==============================================
