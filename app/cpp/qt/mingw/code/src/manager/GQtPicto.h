//===============================================
#ifndef _GQtPicto_
#define _GQtPicto_
//===============================================
#include "GInclude.h"
//===============================================
#define GQTPICTOI GQtPicto::Instance()
#define GQTPICTO(_x, _y) GQTPICTOI->getPicto(_x, _y)
//===============================================
class GQtPicto {
public:
    GQtPicto();
    ~GQtPicto();
    static GQtPicto* Instance();
    QIcon getPicto(int _picto, const QColor& _color);

private:
    static GQtPicto* m_instance;
    QtAwesome* m_QtAwesome;
};
//==============================================
#endif
//==============================================
