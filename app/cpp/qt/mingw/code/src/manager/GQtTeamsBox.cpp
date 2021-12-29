//===============================================
#include "GQtTeamsBox.h"
#include "GQtButtonCircle.h"
#include "GQtTextEdit.h"
#include "GQtLog.h"
//===============================================
GQtTeamsBox::GQtTeamsBox(QWidget* _parent) :
GQtWidget(_parent) {
    m_iconTR = new GQtButtonCircle;
    m_iconTL = new GQtButtonCircle;
    m_iconBR = new GQtButtonCircle;
    m_iconBL = new GQtButtonCircle;
    m_message = new GQtTextEdit;

    m_iconList.push_back(m_iconTL);
    m_iconList.push_back(m_iconTR);
    m_iconList.push_back(m_iconBR);
    m_iconList.push_back(m_iconBL);

    QGridLayout* lMainLayout = new QGridLayout;
    lMainLayout->addWidget(m_iconTL, 0, 0, Qt::AlignTop);
    lMainLayout->addWidget(m_iconBL, 1, 0, Qt::AlignBottom);
    lMainLayout->addWidget(m_message, 0, 1, 2, 1);
    lMainLayout->addWidget(m_iconTR, 0, 2, Qt::AlignTop);
    lMainLayout->addWidget(m_iconBR, 1, 2, Qt::AlignBottom);
    lMainLayout->setMargin(0);

    setLayout(lMainLayout);

    m_index = 0;
    m_text = "NC";
    m_icon = fa::paperplaneo;
    m_type = 0; // 0 : icon ; 1 : text

    updateView();
}
//===============================================
GQtTeamsBox::~GQtTeamsBox() {

}
//===============================================
void GQtTeamsBox::setIndex(int _index) {
    m_index = _index;
    updateView();
}
//===============================================
void GQtTeamsBox::setIndexIcon(int _index, int _icon) {
    m_index = _index;
    m_icon = _icon;
    m_type = 0;
    updateView();
}
//===============================================
void GQtTeamsBox::setIndexText(int _index, const QString& _text) {
    m_index = _index;
    m_text = _text;
    m_type = 1;
    updateView();
}
//===============================================
void GQtTeamsBox::setIcon(int _icon) {
    m_icon = _icon;
    m_type = 0;
    updateView();
}
//===============================================
void GQtTeamsBox::setText(const QString& _text) {
    m_text = _text;
    m_type = 1;
    updateView();
}
//===============================================
void GQtTeamsBox::updateView() {
    m_iconTL->hide();
    m_iconTR->hide();
    m_iconBL->hide();
    m_iconBR->hide();

    if(m_index < 0 || m_index > 3) {
        GQTLOG->addError(QString("Erreur l'index est incorrect : %1")
                .arg(m_index));
        return;
    }

    GQtButtonCircle* lIcon = reinterpret_cast<GQtButtonCircle*>(m_iconList.at(m_index));
    lIcon->show();
    if(m_type == 0) {
        lIcon->setIcon(m_icon);
    }
    else {
        lIcon->setText(m_text);
    }
}
//===============================================
