//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
//===============================================
class GManager {
private:
    GManager();
    
public:
    ~GManager();
    static GManager* Instance();
    sGManager* getData();
    QString getMd5(const QString& data);
    QString getPassword(const QString& username, const QString& password);
    int countUser(const QString& username);
    int countUser(const QString& username, const QString& password);
    void saveUser(const QString& username, const QString& password);
    void insertUser(const QString& username, const QString& password);
    void updateUser(const QString& username, const QString& password);
    QStringList getTableFields(const QString& table);
    QVector<QVector<QString>> getTableData(const QString& table);
    QStringList getDirFiles(const QString& path, const QStringList& filters);
    bool runCmd(const QString& cmd);
    QString readFile(const QString& path);
    void showMessage(QWidget* parent, const QString& title, const QString& text);
    void showWarning(QWidget* parent, const QString& title, const QString& text);
    void showError(QWidget* parent, const QString& title, const QString& text);
    int showQuestion(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Ok | QMessageBox::Cancel);
    void clearLayout(QLayout* layout);
    void setPage(const QString& address);
    void setPage(const QString& address, const QString& newAddress);

private:
    static GManager* m_instance;
    sGManager* mgr;
};
//==============================================
struct _sGManager {
    sGApp* app;
};
//==============================================
struct _sGApp {
    // app
    QString app_name;
    // sqlite
    QString sqlite_driver;
    QString sqlite_db_path;
};
//==============================================
#endif
//==============================================
