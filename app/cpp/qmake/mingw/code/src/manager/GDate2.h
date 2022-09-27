//===============================================
#ifndef _GDate2_
#define _GDate2_
//===============================================
#include "GObject2.h"
//===============================================
class GDate2 : public GObject2 {
    Q_OBJECT

public:
    GDate2(QObject* _parent = 0);
    ~GDate2();
    GString getDateTimeLogFormat() const;
    GString getDateTimeFileFormat() const;
    GString getDateFileFormat() const;
    GString getDate(const GString& _format) const;
};
//==============================================
#endif
//==============================================
