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
	QString getPadItem(const QString& _data) const;
	QString getPadWindowItem(const QString& _data) const;
	QString getPadWindowItem(int _i, const QString& _data) const;
	int countPadWindowItem() const;
	void createWindow();
	QWidget* createHeader();
};
//===============================================
#endif
//===============================================
