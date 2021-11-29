//===============================================
#ifndef _GQtTableWidget_
#define _GQtTableWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GQtTableWidget : public QTableWidget {
    Q_OBJECT

public:
    GQtTableWidget(QWidget* _parent = 0);
    ~GQtTableWidget();
    static GQtTableWidget* Create(const QString& _key, QWidget* _parent = 0);
    virtual bool saveFile(const QString &fileName);
    virtual bool loadFile(const QString &fileName);
    virtual bool getAutoRecalculate();;

public slots:
    virtual void setAutoRecalculate(bool _recalc);
};
//==============================================
#endif
//==============================================
