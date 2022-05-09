//===============================================
#ifndef _GQtDialog_
#define _GQtDialog_
//===============================================
#include "GInclude.h"
//===============================================
class GQtXml;
//===============================================
class GQtDialog : public QDialog {
    Q_OBJECT

public:
    GQtDialog(QWidget* _parent = 0);
    ~GQtDialog();

protected:
    QSharedPointer<GQtXml> m_dom;
};
//==============================================
#endif
//==============================================
