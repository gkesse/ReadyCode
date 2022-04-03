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
    void addError(const QString& _error);
    QString toString() const;
    bool hasErrors() const;
    void clearErrors();
    void loadErrors(const QString& _res);
    QVector<QString>& getErrors();

private:
    QVector<QString> m_errors;
};
//==============================================
#endif
//==============================================
