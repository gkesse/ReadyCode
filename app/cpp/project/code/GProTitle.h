//===============================================
#ifndef _GProTitle_
#define _GProTitle_
//===============================================
#include "GProUi.h"
//===============================================
class GProTitle : public GProUi {
    Q_OBJECT
    
public:
    GProTitle(QWidget* parent = 0);
    ~GProTitle();
    void setTitle(const QString& text);

public slots:
	void onEvent();
	void onEvent(const QString& text);

private:
	QMap<QWidget*, QString> m_widgetMap;
	QPushButton* m_title;
};
//==============================================
#endif
//==============================================
