//===============================================
#ifndef _GMainWindow_
#define _GMainWindow_
//===============================================
#include "GInclude.h"
//===============================================
class GCode;
class GError;
//===============================================
class GMainWindow : public QMainWindow {
	Q_OBJECT

public:
	GMainWindow(QWidget* _parent = 0);
	virtual ~GMainWindow();
	virtual void createDoms();
	virtual QString getItem(const QString& _code, const QString& _key) const;
	virtual QString getItem(const QString& _code, const QString& _key, int _index) const;
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
