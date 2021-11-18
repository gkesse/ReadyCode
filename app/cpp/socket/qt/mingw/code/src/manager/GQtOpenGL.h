//===============================================
#ifndef _GQtOpenCV_
#define _GQtOpenCV_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtOpenGL : public GQtWidget {
    Q_OBJECT

public:
    GQtOpenGL(QWidget* _parent = 0);
    ~GQtOpenGL();

private:
    QMap<QWidget*, QString> m_QWidgetMap;
};
//==============================================
#endif
//==============================================
