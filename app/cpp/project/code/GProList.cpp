//===============================================
#include "GProList.h"
#include "GManager.h"
//===============================================
GProList::GProList(QWidget* parent) :
GProUi(parent) {
    QVBoxLayout* lScrollLayout = new QVBoxLayout;
    m_scrollLayout = lScrollLayout;
    lScrollLayout->setAlignment(Qt::AlignTop);
    lScrollLayout->setMargin(0);
    lScrollLayout->setSpacing(0);

    QFrame* lScrollWidget = new QFrame;
    lScrollWidget->setLayout(lScrollLayout);

    QScrollArea* lScrollArea = new QScrollArea;
    lScrollArea->setWidget(lScrollWidget);
    lScrollArea->setWidgetResizable(true);

    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lScrollArea);
    lMainLayout->setAlignment(Qt::AlignTop);
    lMainLayout->setMargin(0);
    lMainLayout->setSpacing(0);

    setLayout(lMainLayout);
}
//===============================================
GProList::~GProList() {
    
}
//===============================================
void GProList::addItem(QString key, QString text) {
    QPushButton* lButton = new QPushButton;
    lButton->setText(text);
    lButton->setCursor(Qt::PointingHandCursor);
    lButton->setStyleSheet("text-align:center;");
    m_scrollLayout->addWidget(lButton);
    m_widgetId[lButton] = key;
    connect(lButton, SIGNAL(clicked()), this, SLOT(slotEvent()));
}
//===============================================
void GProList::slotEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetId[lWidget];
    emit emitEvent(lWidgetId);
}
//===============================================
