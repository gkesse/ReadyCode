//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
class GError;
//===============================================
class GObject : public QObject {
	Q_OBJECT

public:
    GObject(QObject* _parent = 0);
	virtual ~GObject();
	virtual void createDoms();
    virtual QString getItem(const QString& _code, const QString& _key) const;
    virtual QString getItem(const QString& _code, int _index, bool _isCData = false) const;
    virtual int countItem(const QString& _code) const;
	QSharedPointer<GError>& getErrors();
	virtual void runDefault(int _argc, char** _argv);

protected:
	QSharedPointer<GCode> m_dom;
    QSharedPointer<GError> m_errors;
};
//===============================================
#endif
//===============================================
