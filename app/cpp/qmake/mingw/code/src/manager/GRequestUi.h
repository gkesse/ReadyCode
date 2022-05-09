//===============================================
#ifndef _GRequestUi_
#define _GRequestUi_
//===============================================
#include "GDialog.h"
//===============================================
class GRequest;
//===============================================
class GRequestUi : public GDialog {
	Q_OBJECT

public:
	GRequestUi(QWidget* _parent = 0);
	~GRequestUi();
	void createDoms();
	void createLayout();
	//
    void onRequestSend();
    void onRequestClear();
    void onRequestSearch();
	void onRequestSearchNext();
	void onRequestSearchPrevious();
	void getRequestList(int _newOffset = 0);

public slots:
    void onEvent();
    void onEvent(const QString& _text);

private:
    int m_dataOffset;
    int m_dataSize;
    QSharedPointer<GRequest> m_reqs;
};
//===============================================
#endif
//===============================================
