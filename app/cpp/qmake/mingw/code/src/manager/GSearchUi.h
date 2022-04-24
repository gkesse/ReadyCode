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
	//
    void setRows(int _rows);
    void setCols(int _cols);
    void setReadonlyOn(bool _isReadonlyOn);
    void setSelectRowOn(bool _isSelectRowOn);
    void setHorHeaderOn(bool _isHorHeaderOn);
    void setVerHeaderOn(bool _isVerHeaderOn);
    void setHorHeaderStretchLastOn(bool _isHorHeaderStretchLastOn);
    void setVerHeaderStretchLastOn(bool _isVerHeaderStretchLastOn);
    //
	void loadData();

public slots:
    void onEvent();
    void onEvent(const QString& _text);
    void onClick(QTableWidgetItem* _item);
    void onDoubleClick(QTableWidgetItem* _item);

private:
    std::vector<std::vector<std::string>> m_dataMap;
    //
    int m_rows;
    int m_cols;
    //
    bool m_readonlyOn;
    bool m_selectRowOn;
    bool m_horHeaderOn;
    bool m_verHeaderOn;
    bool m_horHeaderStretchLastOn;
    bool m_verHeaderStretchLastOn;
};
//===============================================
#endif
//===============================================
