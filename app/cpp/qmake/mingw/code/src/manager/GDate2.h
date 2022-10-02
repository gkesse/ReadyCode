//===============================================
#ifndef _GDate2_
#define _GDate2_
//===============================================
#include "GObject.h"
//===============================================
class GDate2 : public GObject {
public:
    GDate2();
    ~GDate2();
    GString getDateTimeLogFormat() const;
    GString getDateTimeFileFormat() const;
    GString getDateFileFormat() const;
    GString getDate(const GString& _format) const;
};
//==============================================
#endif
//==============================================
