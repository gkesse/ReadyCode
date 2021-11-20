//===============================================
#ifndef _GQtDialog_
#define _GQtDialog_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GQtDialog : public QDialog {
    Q_OBJECT

public:
    GQtDialog(QWidget* _parent = 0);
    ~GQtDialog();
    static GQtDialog* Create(const QString& _key);

signals:
    void onEmit(const QString& _text);

protected:
    QMap<QWidget*, QString> m_QWidgetMap;
};
//==============================================
#endif
//==============================================
