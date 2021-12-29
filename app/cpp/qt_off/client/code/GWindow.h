//================================================
#ifndef _GWindow_
#define _GWindow_
//================================================
#include <QApplication>
#include <QtWidgets>
#include <QtDBus/QtDBus>
//================================================
class GWindow : public QFrame {
    Q_OBJECT
    
public:
    GWindow(QWidget* parent = 0);
    ~GWindow();
};
//================================================
#endif
//================================================