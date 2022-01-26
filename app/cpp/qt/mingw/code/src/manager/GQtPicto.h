//===============================================
#ifndef _GQtPicto_
#define _GQtPicto_
//===============================================
#include "GQtObject.h"
//===============================================
#define GQTPICTOI GQtPicto::Instance()
#define GQTPICTO(_x, _y) GQTPICTOI->getPicto(_x, _y)
//===============================================
class GQtPicto : public GQtObject {
    Q_OBJECT

public:
    GQtPicto(QObject* _parent = 0);
    ~GQtPicto();
    static GQtPicto* Instance();
    QIcon getPicto(const QString& _picto, const QColor& _color);
    QIcon getPictoId(int _picto, const QColor& _color);

private:
    static GQtPicto* m_instance;
    QtAwesome* m_QtAwesome;
};
//==============================================
#endif
//==============================================
