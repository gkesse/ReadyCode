//===============================================
#ifndef _GDate_
#define _GDate_
//===============================================
#include "GObject.h"
//===============================================
class GDate : public GObject {
public:
    GDate();
    ~GDate();
    std::string getLogFormat() const;
    std::string getDate(const std::string& _format);
};
//==============================================
#endif
//==============================================
