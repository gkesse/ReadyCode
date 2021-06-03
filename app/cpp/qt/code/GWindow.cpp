//================================================
#include "GWindow.h"
#include "GDBusInterface.h"
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {
    if (!QDBusConnection::sessionBus().isConnected()) {
        qDebug() << "[error] connexion dbus";
        return;
    }

    QDBusConnection::sessionBus().registerObject("/", this);
    GDBusInterface* lInterface = new GDBusInterface(QString(), QString(), QDBusConnection::sessionBus(), this);

    QPushButton* lSend = new QPushButton;
    lSend->setText("Send");
    m_widgetMap[lSend] = "send";

    QHBoxLayout* lButtonLayout = new QHBoxLayout;
    lButtonLayout->addWidget(lSend);
    lButtonLayout->setAlignment(Qt::AlignLeft);
    
    QTextEdit* lTextEdit = new QTextEdit;
    lTextEdit->setReadOnly(true);
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lButtonLayout);
    lMainLayout->addWidget(lTextEdit);

    setLayout(lMainLayout);
    
    connect(lSend, SIGNAL(clicked()), this, SLOT(slotClick()));
    connect(lInterface, SIGNAL(emitMessage(QString, QString)), this, SLOT(slotMessage(QString, QString)));
    emit emitMessage("connection", "gkesse vient de se connecter !");
}
//================================================
GWindow::~GWindow() {

}
//================================================
void GWindow::slotClick() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];
    onEvent(lWidgetId);
}
//================================================
void GWindow::slotMessage(const QString& key, const QString& value) {
    m_key = key;
    m_value = value;
    onEvent("dbus_message");
}
//================================================
void GWindow::onEvent(const QString& event) {
    qDebug() << "event : " << event;
    qDebug() << "m_key : " << m_key;
    qDebug() << "m_value : " << m_value;
}
//================================================
