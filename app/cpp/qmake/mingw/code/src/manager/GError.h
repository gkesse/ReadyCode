//===============================================
#ifndef _GError_
#define _GError_
//===============================================
#include "GObject.h"
//===============================================
class GError : public GObject {
    Q_OBJECT

public:
    GError(QObject* _parent = 0);
    ~GError();
    //
    void addError(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _error);
    QString toString() const;
    bool hasErrors() const;
    void clearErrors();
    void loadErrors(const char* _name, int _level, const char* _file, int _line, const char* _func, const QString& _res);
    QVector<QString>& getErrors();

private:
    QVector<QString> m_errors;
};
//==============================================
#endif
//==============================================
