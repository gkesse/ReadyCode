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
    GString getDateTimeLogFormat() const;
    GString getDateTimeFileFormat() const;
    GString getDateFileFormat() const;
    GString getDate(const GString& _format) const;
};
//==============================================
#endif
//==============================================
