//===============================================
#ifndef _GQtPicto_
#define _GQtPicto_
//===============================================
#include "GInclude.h"
//===============================================
#define GQTPICTOI GQtPicto::Instance()
#define GQTPICTO(_x) GQTPICTOI->getPicto(_x)
#define GQTPICTOC(_x, _y) GQTPICTOI->getPictoColor(_x, _y)
//===============================================
class GQtPicto {
public:
    GQtPicto();
    ~GQtPicto();
    static GQtPicto* Instance();
    void setPicto(const QColor& _color);
    QIcon getPicto(int _picto);
    QIcon getPictoColor(int _picto, const QColor& _color);

private:
    static GQtPicto* m_instance;
    QtAwesome* m_QtAwesome;
};
//==============================================
#endif
//==============================================
