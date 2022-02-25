//===============================================
#include "GLogin.h"
#include "GPath.h"
#include "GXml.h"
//===============================================
GLogin::GLogin(QWidget* _parent) :
GWidget(_parent) {
	createDoms();

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	setLayout(lMainLayout);

	QString lTitle = getItem("title");

	setWindowTitle(lTitle);
}
//===============================================
GLogin::~GLogin() {

}
//===============================================
void GLogin::createDoms() {
	m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "app.xml"));
    m_dom->createXPath();
}
//===============================================
QString GLogin::getItem(const QString& _data) const {
    m_dom->queryXPath(QString("/rdv/datas/data[code='login']/%1").arg(_data));
    m_dom->getNodeXPath();
    QString lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
