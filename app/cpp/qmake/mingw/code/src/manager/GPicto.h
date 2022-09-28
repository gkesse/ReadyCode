//===============================================
#ifndef _GPicto_
#define _GPicto_
//===============================================
#include "GObject.h"
//===============================================
#define GPICTOI GPicto::Instance()
#define GPICTO(_x, _y) GPICTOI->getPicto(_x, _y)
//===============================================
class GPicto : public GObject {
public:
    GPicto();
    ~GPicto();
    static GPicto* Instance();
    QIcon getPicto(const QString& _picto, const QColor& _color);
    QIcon getPictoId(int _picto, const QColor& _color);

private:
    static GPicto* m_instance;
    QtAwesome* m_QtAwesome;
};
//==============================================
#endif
//==============================================
