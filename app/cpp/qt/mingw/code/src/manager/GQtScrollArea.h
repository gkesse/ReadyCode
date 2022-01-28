//===============================================
#ifndef _GQtScrollArea_
#define _GQtScrollArea_
//===============================================
#include "GInclude.h"
//===============================================
class GQtScrollArea : public QScrollArea {
    Q_OBJECT

public:
    GQtScrollArea(QWidget* _parent = 0);
    ~GQtScrollArea();

protected:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
};
//==============================================
#endif
//==============================================
