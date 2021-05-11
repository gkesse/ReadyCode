//================================================
#ifndef _GWindow_
#define _GWindow_
//================================================
#include <QtWidgets>
//================================================
struct sGUser;
//================================================
class GWindow : public QMainWindow {
    Q_OBJECT
    
public:
    GWindow(QWidget* parent = 0);
    ~GWindow();
    
private:
    void loadData();
    void saveData();
    void showData();
    void addData();

public slots:
    void onClick();
    
private:
    QVector<sGUser> m_userMap;
    QTextEdit* m_textEdit;
    int m_index;
};
//================================================
struct sGUser {
    int id;
    QString name;
    QString email;
};
//================================================
inline QDataStream& operator<<(QDataStream& stream, const sGUser& user) {
    return stream << user.id << user.name << user.email;
}
//================================================
inline QDataStream& operator>>(QDataStream& stream, sGUser& user) {
    return stream >> user.id >> user.name >> user.email;
}
//================================================
#endif
//================================================