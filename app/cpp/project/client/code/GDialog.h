//================================================
#ifndef _GDialog_
#define _GDialog_
//================================================
#include <QtWidgets>
//================================================
class GDialog : public QDialog {
    Q_OBJECT
    
public:
    GDialog(QWidget* parent = 0);
    ~GDialog();
};
//================================================
#endif
//================================================
