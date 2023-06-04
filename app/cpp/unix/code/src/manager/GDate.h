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

    void setFormat(const GString& _format);
    GString getDate() const;
    bool run();

public:
    static const char* DATE_LOGTRACE;
    static const char* DATE_FILENAME;
    static const char* DATETIME_LOGTRACE;
    static const char* DATETIME_FILENAME;
private:
    GString m_format;
    GString m_date;
};
//==============================================
#endif
//==============================================
