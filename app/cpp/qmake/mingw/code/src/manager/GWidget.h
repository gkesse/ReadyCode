//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GXml;
//===============================================
class GWidget : public QFrame {
	Q_OBJECT

public:
	GWidget(QWidget* _parent = 0);
	virtual ~GWidget();
	void addObject(QObject* _object, const QString& _key);
	QObject* getObject(const QString& _key);

protected:
	QSharedPointer<GXml> m_dom;
	QMap<QObject*, QString> m_objectMap;
};
//===============================================
#endif
//===============================================
