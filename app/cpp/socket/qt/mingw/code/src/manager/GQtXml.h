//===============================================
#ifndef _GInterfaceXml_
#define _GInterfaceXml_
//===============================================
#include "GQtWidget.h"
#include "GQt.h"
//===============================================
class GQtXml : public GQtWidget {
    Q_OBJECT

public:
    GQtXml(QWidget* _parent = 0);
    ~GQtXml();

public slots:
    void onEvent();

private:
    QMap<QWidget*, QString> m_QWidgetMap;
    GQt m_textEdit;
};
//==============================================
#endif
//==============================================
