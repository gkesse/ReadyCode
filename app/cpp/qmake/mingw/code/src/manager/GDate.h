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
    QString getDateTimeLogFormat() const;
    QString getDateTimeFileFormat() const;
    QString getDateFileFormat() const;
    QString getDate(const QString& _format) const;
};
//==============================================
#endif
//==============================================
