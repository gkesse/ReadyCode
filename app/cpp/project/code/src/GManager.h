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
    // data
    void setData(QTextEdit* textEdit, const QVector<QString>& data);
    void setData(QTextEdit* textEdit, const QVector<QVector<QString>>& data);
  	void setData(QComboBox* comboBox, const QVector<QString>& data);
    void setData2(QTextEdit* textEdit, const QVector<QString>& data);
    void setData2(QComboBox* comboBox, const QVector<QString>& data);
    // user
    int countUser(const QString& username);
    int countUser(const QString& username, const QString& password);
    QString getUserId(const QString& username);
    void saveUser(const QString& username, const QString& password);
    void insertUser(const QString& username, const QString& password);
    void updateUser(const QString& username, const QString& password);
    QString getPassword(const QString& username, const QString& password);
    // login
    int countLogin();
    int countLogin(QString username);
    void saveLogin(const QString& username, const QString& login);
    void insertLogin(QString username, QString login);
    void updateLogin(QString username, QString login);
    void updateLogin();
    void logOut();
    // file_id
    int countFileId(const QString& fileId);
    void insertFileId(const QString& fileId);
    // sqlite
    QVector<QString> getTables();
    QVector<QVector<QString>> getData(const QString& table);
    QString getSchema(const QString& table);
    void deleteTable(const QString& table);
    QStringList getFields(const QString& table);
    // file
    QStringList getDirFiles(const QString& path, const QStringList& filters);
    QString readFile(const QString& path);
    // message
    void showMessage(QWidget* parent, const QString& title, const QString& text);
    void showWarning(QWidget* parent, const QString& title, const QString& text);
    void showError(QWidget* parent, const QString& title, const QString& text);
    int showQuestion(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Ok | QMessageBox::Cancel);
    int confirm(QWidget* parent);
    // divers
    QString getMd5(const QString& data);
    bool runCmd(const QString& cmd);
    bool runCmd(const QString& cmd, QString& output);
    bool runCmd2(const QString& cmd);

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
    QString sqlite_sql_path;
    QString sqlite_sql_master;
    QString sqlite_sql_tmp;
    QString sqlite_table_name;
    // login
    QPushButton* login_connect;
    QPushButton* login_disconnect;
};
//==============================================
#endif
//==============================================
