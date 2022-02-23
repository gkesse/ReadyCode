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
	~GWidget();

protected:
	QSharedPointer<GXml> m_dom;
};
//===============================================
#endif
//===============================================
