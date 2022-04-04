//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
class GError;
//===============================================
class GWidget : public QFrame {
	Q_OBJECT

public:
	GWidget(QWidget* _parent = 0);
	virtual ~GWidget();
	virtual QString getItem(const QString& _code, const QString& _data) const;
	virtual QString getItem(const QString& _code, const QString& _data, int _i) const;
	virtual int countItem(const QString& _code) const;
	void addObject(QObject* _object, const QString& _key);
	QObject* getObject(const QString& _key);

protected:
	QSharedPointer<GXml> m_dom;
	QMap<QObject*, QString> m_objectMap;
    QSharedPointer<GError> m_errors;
};
//===============================================
#endif
//===============================================
