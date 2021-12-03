//===============================================
#ifndef _GQtXml_
#define _GQtXml_
//===============================================
#include "GQtWidget.h"
//===============================================
class GQtTextEdit;
class GQtButtonCircle;
class GQtTeamsBox;
//===============================================
class GQtXml : public GQtWidget {
    Q_OBJECT

public:
    GQtXml(QWidget* _parent = 0);
    ~GQtXml();

public slots:
    void onEvent();

protected:
    GQtTextEdit* m_GQtTextEdit;
    GQtButtonCircle* m_GQtButtonCircle;
    GQtTeamsBox* m_GQtTeamsBox;
};
//==============================================
#endif
//==============================================
