//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
class GError;
//===============================================
class GWidget : public QFrame {
	Q_OBJECT

public:
	GWidget(QWidget* _parent = 0);
	virtual ~GWidget();
	virtual void createDoms();
	virtual QString getItem(const QString& _code, const QString& _key) const;
	virtual QString getItem(const QString& _code, const QString& _key, int _index) const;
	virtual QString getItem(const QString& _code, const QString& _category, const QString& _key, bool _isCData = false);
	virtual int countItem(const QString& _code) const;
	void addObject(QObject* _object, const QString& _key);
    QObject* getObject(const QString& _key);
    QString getObject(QObject* _key, const QString& _defaultValue = "");

protected:
	QSharedPointer<GCode> m_dom;
	QMap<QObject*, QString> m_objectMap;
    QSharedPointer<GError> m_errors;
};
//===============================================
#endif
//===============================================
