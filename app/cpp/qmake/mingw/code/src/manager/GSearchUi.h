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
    void setReadonlyOn(bool _isReadonlyOn);
    void setSelectRowOn(bool _isSelectRowOn);
    void setHorHeaderOn(bool _isHorHeaderOn);
    void setVerHeaderOn(bool _isVerHeaderOn);
    void setHorHeaderStretchLastOn(bool _isHorHeaderStretchLastOn);
    void setVerHeaderStretchLastOn(bool _isVerHeaderStretchLastOn);
    //
	void loadData();
	int getCurrentIndex() const;

public slots:
    void onEvent();
    void onEvent(const QString& _text);
    void onClick(QTableWidgetItem* _item);
    void onDoubleClick(QTableWidgetItem* _item);

private:
    bool m_readonlyOn;
    bool m_selectRowOn;
    bool m_horHeaderOn;
    bool m_verHeaderOn;
    bool m_horHeaderStretchLastOn;
    bool m_verHeaderStretchLastOn;
    QTableWidgetItem* m_currentItem;
    int m_currentIndex;
};
//===============================================
#endif
//===============================================
