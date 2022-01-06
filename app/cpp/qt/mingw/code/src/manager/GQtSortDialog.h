//===============================================
#ifndef _GQtSortDialog_
#define _GQtSortDialog_
//===============================================
#include "GQtDialog.h"
//===============================================
class GQtSortBox;
//===============================================
class GQtSortDialog : public GQtDialog {
    Q_OBJECT

public:
    GQtSortDialog(QWidget* _parent = 0);
    ~GQtSortDialog();
    void createDoms();
    QString getTitle() const;
    int getWidth() const;
    int getHeight() const;
    void setColumnRange(QChar first, QChar last);
    int currentIndexColumnCombo(int _index) const;
    int currentIndexOrderCombo(int _index) const;

public slots:
    void onMoreButton();

private:
    GQtSortBox* primarySortBox;
    GQtSortBox* secondarySortBox;
    GQtSortBox* tertiarySortBox;
};
//==============================================
#endif
//==============================================
