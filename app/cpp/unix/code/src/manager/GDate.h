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
    std::string getDateTimeLogFormat() const;
    std::string getDateTimeFileFormat() const;
    std::string getDateFileFormat() const;
    std::string getDate(const std::string& _format) const;
};
//==============================================
#endif
//==============================================
