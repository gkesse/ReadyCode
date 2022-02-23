//===============================================
#ifndef _GPad_
#define _GPad_
//===============================================
#include "GWidget.h"
//===============================================
class GPad : public GWidget {
	Q_OBJECT

public:
	GPad(QWidget* _parent = 0);
	~GPad();
	void createDoms();
	int countPadItem() const;
	QString getPadItem(const QString& _data) const;
	QString getPadItem(int _i, const QString& _data) const;
	int countLoginItem() const;
	QString getLoginItem(const QString& _data) const;
	QString getLoginItem(int _i, const QString& _data) const;
	void createPad();
	QDialog* createLogin(QWidget* _parent = 0);

public slots:
	void onEvent();
};
//===============================================
#endif
//===============================================
