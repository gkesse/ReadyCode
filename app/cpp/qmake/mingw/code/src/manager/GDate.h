//===============================================
#ifndef _GDate_
#define _GDate_
//===============================================
#include "GObject.h"
//===============================================
class GDate : public GObject {
    Q_OBJECT

public:
    GDate(QObject* _parent = 0);
    ~GDate();
    QString getDateTimeLogFormat() const;
    QString getDateTimeFileFormat() const;
    QString getDateFileFormat() const;
    QString getDate(const QString& _format) const;
};
//==============================================
#endif
//==============================================
