//================================================
#ifndef _GWindow_
#define _GWindow_
//================================================
#include <QApplication>
#include <QtWidgets>
//================================================
class GWindow : public QFrame {
    Q_OBJECT
    
public:
    GWindow(QWidget* parent = 0);
    ~GWindow();

public:
    void onEvent(const QString& event);

public slots:
    void slotClick();
    
private:
    QMap<QWidget*, QString> m_widgetMap;
    QTextEdit* m_textEdit;
    QString m_filename;
};
//================================================
#endif
//================================================