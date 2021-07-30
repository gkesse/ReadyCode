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
    void showMessage(QWidget* parent, const QString& title, const QString& text);
    void showWarning(QWidget* parent, const QString& title, const QString& text);
    void showError(QWidget* parent, const QString& title, const QString& text);
    int showQuestion(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Ok | QMessageBox::Cancel);

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
