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
    void initDate();
    GString getDateTimeLogFormat() const;
    GString getDateTimeFileFormat() const;
    GString getDateFileFormat() const;
    GString getDate(const GString& _format) const;

private:
    GString m_dateTimeLogFormat;
    GString m_dateTimeFileFormat;
    GString m_dateFileFormat;
};
//==============================================
#endif
//==============================================
