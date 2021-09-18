//===============================================
#ifndef _GDialogUi_
#define _GDialogUi_
//===============================================
#include "GInclude.h"
//===============================================
class GDialogUi : public QDialog {
	Q_OBJECT

public:
	GDialogUi(QWidget* parent = 0);
	virtual ~GDialogUi();
	static GDialogUi* Create(const QString& key, QWidget* parent = 0);
	virtual QMap<QString, QString> getData();

public slots:
	virtual void onEvent();
	virtual void onEvent(const QString& text);

protected:
	QMap<QString, QString> m_dataMap;
};
//==============================================
#endif
//==============================================
