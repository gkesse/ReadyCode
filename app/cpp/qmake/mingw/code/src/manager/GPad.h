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
    void createPad();
    QWidget* createHeader();
	QDialog* createLogin(QWidget* _parent = 0);
	bool hasErrors() const;
	void addErrors(const QString& _errors);
	QString getErrors() const;
	void clearErrors();

public slots:
	void onEvent();
	void onEvent(const QString& _text);

protected:
	bool eventFilter(QObject* _obj, QEvent* _event);

private:
	QVector<QString> m_errors;
	QDialog* m_loginDialog;
};
//===============================================
#endif
//===============================================
