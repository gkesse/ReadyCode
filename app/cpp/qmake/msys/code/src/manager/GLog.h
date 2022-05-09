//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GObject.h"
//===============================================
#define GLOG GLog::Instance()
//===============================================
class GLog : public GObject {
	Q_OBJECT

public:
    GLog(QObject* _parent = 0);
    ~GLog();
    static GLog* Instance();
    void addError(const QString& _error);
    void showError();
    void showError(QWidget* _parent);
    bool hasError();

private:
    static GLog* m_instance;
    //
    QVector<QString> m_errors;
};
//==============================================
#endif
//==============================================
