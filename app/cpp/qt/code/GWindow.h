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
    void updateView(const QString& event);
    
public slots:
    void slotClick();
    void slotDBusMessage(const QString& key, const QString& value);

signals:
    void emitDBusMessage(const QString& key, const QString& value);

private:
    QMap<QWidget*, QString> m_widgetMap;
    QString m_key;
    QString m_value;
    QLineEdit* m_usernameEdit;
    QString m_username;
    QLabel* m_usernameLabel;
    QLineEdit* m_messageEdit;
    QTextEdit* m_textEdit;
    QFrame* m_connectWidget;
    QFrame* m_disconnectWidget;
    QFrame* m_messageWidget;
};
//================================================
#endif
//================================================