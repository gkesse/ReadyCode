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
	bool hasErrors() const;
	void addErrors(const QString& _errors);
	QString getErrors() const;
	void clearErrors();

public slots:
	void onEvent();

protected:
	bool eventFilter(QObject* _obj, QEvent* _event);

private:
	QVector<QString> m_errors;
	QDialog* m_loginDialog;
};
//===============================================
#endif
//===============================================
