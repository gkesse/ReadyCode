//===============================================
#include "GPadUi.h"
#include "GPath.h"
#include "GXml.h"
#include "GStyle.h"
#include "GPicto.h"
#include "GLog.h"
#include "GLoginUi.h"
//===============================================
GPadUi::GPadUi(QWidget* _parent) :
GWidget(_parent) {
	GSTYLE(GRES("css", "style.css"));
	createDoms();
	createLayout();
}
//===============================================
GPadUi::~GPadUi() {

}
//===============================================
void GPadUi::createDoms() {
	m_dom.reset(new GXml);
    m_dom->loadXmlFile(GRES("xml", "pad.xml"));
    m_dom->createXPath();
}
//===============================================
void GPadUi::createLayout() {
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(createHeader());
    lMainLayout->addStretch();
    lMainLayout->setMargin(10);
    lMainLayout->setSpacing(10);

    QString lStyle = getItem("pad", "style");
    QString lTitle = getItem("pad", "title");
    QString lLogo = getItem("pad", "logo");
    int lWidth = getItem("pad", "width").toInt();
    int lHeight = getItem("pad", "height").toInt();

    setLayout(lMainLayout);
    setObjectName(lStyle);

    setWindowTitle(lTitle);
    setWindowIcon(QIcon(GRES("img", lLogo)));
    resize(lWidth, lHeight);

    addObject(new GLoginUi(this), "login/ui");
}
//===============================================
QWidget* GPadUi::createHeader() {
    QFrame* lPage = new QFrame;

    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(10);

    int lCount = countItem("header");
    QString lStyle = getItem("header", "style");

    for(int i = 0; i < lCount; i++) {
        QString lType = getItem("header", "type", i);
        QString lKey = getItem("header", "key", i);
        QString lText = getItem("header", "text", i);
        QString lStyle = getItem("header", "style", i);
        QString lPicto = getItem("header", "picto", i);
        QString lPictoColor = getItem("header", "picto_color", i);
        int lPictoSize = getItem("header", "picto_size", i).toInt();

        if(lType == "spacer") {
            lMainLayout->addStretch();
        }
        else if(lType == "button") {
            QPushButton* lButton = new QPushButton;
            addObject(lButton, lKey);
            lButton->setObjectName(lStyle);
            lButton->setText(lText);
            lButton->setCursor(Qt::PointingHandCursor);
            if(lPicto != "" && lPictoColor != "") {
                lButton->setIcon(GPICTO(lPicto, lPictoColor));
            }
            if(lPictoSize != 0) {
                lButton->setIconSize(QSize(lPictoSize, lPictoSize));
            }
            connect(lButton, SIGNAL(clicked()), this, SLOT(onEvent()));
            lMainLayout->addWidget(lButton);
        }
    }

    lPage->setLayout(lMainLayout);
    lPage->setObjectName(lStyle);
    return lPage;
}
//===============================================
void GPadUi::onEvent() {
    QString lKey = m_objectMap[sender()];
    GLOGT(eGINF, lKey);
    //===============================================
    // header/connect
    //===============================================
    if(lKey == "header/connect") {
    	QDialog* lLoginUi = qobject_cast<GLoginUi*>(getObject("login/ui"));
    	lLoginUi->exec();
    }
    //===============================================
    // else
    //===============================================
    else {
    	GERROR(eGERR, QString("Erreur la cle n'existe pas.\n"
    			"- cle : (%1)").arg(lKey));
    }
    //===============================================
    // end
    //===============================================
    GERROR_SHOWG(eGERR);
}
//===============================================
void GPadUi::onEvent(const QString& _text) {

}
//===============================================
bool GPadUi::eventFilter(QObject* _obj, QEvent* _event) {
    return QObject::eventFilter(_obj, _event);
}
//===============================================
