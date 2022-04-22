//===============================================
#ifndef _GSearchUi_
#define _GSearchUi_
//===============================================
#include "GDialog.h"
//===============================================
class GSearchUi : public GDialog {
	Q_OBJECT

public:
	GSearchUi(QWidget* _parent = 0);
	~GSearchUi();
	void createDoms();
	void createLayout();

public slots:
    void onEvent();
    void onEvent(const QString& _text);

private:
    std::vector<std::vector<std::string>> m_dataMap;
    int m_rows;
    int m_cols;
};
//===============================================
#endif
//===============================================
