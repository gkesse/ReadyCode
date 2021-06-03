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
    
public:
    void onEvent(const QString& event);
    
public slots:
    void slotClick();
    void slotMessage(const QString& key, const QString& value);

signals:
    void emitMessage(const QString& key, const QString& value);

private:
    QMap<QWidget*, QString> m_widgetMap;
    QString m_key;
    QString m_value;
};
//================================================
#endif
//================================================