//===============================================
#include "GQtXml.h"
#include "GQtButtonCircle.h"
#include "GQtTextEdit.h"
#include "GQtTeamsBox.h"
#include "GStruct.h"
#include "GQtLog.h"
//===============================================
GQtXml::GQtXml(QWidget* _parent) :
GQtWidget(_parent) {
    sGQt lParams;
    lParams.app_name = "ReadyApp-XML";

    QPushButton* lTest = new QPushButton("Tester");

    m_GQtButtonCircle = new GQtButtonCircle;
    m_GQtTextEdit = new GQtTextEdit;
    m_GQtTeamsBox = new GQtTeamsBox;

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lTest);
    lMainLayout->addWidget(m_GQtButtonCircle);
    lMainLayout->addWidget(m_GQtTextEdit);
    lMainLayout->addWidget(m_GQtTeamsBox);
    lMainLayout->setAlignment(Qt::AlignBottom);

    setLayout(lMainLayout);
    setWindowTitle(lParams.app_name);
    resize(lParams.width, lParams.height);

    connect(lTest, SIGNAL(clicked()), this, SLOT(onEvent()));

    GQTLOG->showErrorQt(this);
}
//===============================================
GQtXml::~GQtXml() {

}
//===============================================
void GQtXml::onEvent() {
    m_GQtButtonCircle->setBgColor("navy");
    m_GQtButtonCircle->setText("NC");
    m_GQtTextEdit->setBgColor("navy");
    m_GQtTextEdit->setHoverColor("teal");
    m_GQtTeamsBox->setIndexText(2, "NC");
    qDebug() << m_GQtTextEdit->getText();
}
//===============================================
