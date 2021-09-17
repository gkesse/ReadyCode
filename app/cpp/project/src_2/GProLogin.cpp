//===============================================
#include "GProLogin.h"
//===============================================
GProLogin::GProLogin(QWidget* parent) :
GProUi(parent) {
	// layout
	QVBoxLayout* lMainLayout = new  QVBoxLayout;
	lMainLayout->setAlignment(Qt::AlignCenter);

	setLayout(lMainLayout);
}
//===============================================
GProLogin::~GProLogin() {

}
//===============================================
