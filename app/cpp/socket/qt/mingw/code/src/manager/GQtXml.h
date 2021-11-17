//===============================================
#ifndef _GInterfaceXml_
#define _GInterfaceXml_
//===============================================
#include "GWidget.h"
//===============================================
class GQtXml : public GWidget {
    Q_OBJECT

public:
    GQtXml(QWidget* _parent = 0);
    ~GQtXml();

public slots:
    void onEvent();

private:
    QTextEdit* m_textEdit;
};
//==============================================
#endif
//==============================================
