//================================================
#include "GWindow.h"
#include "GDBusInterface.h"
#include "GDBusAdaptor.h"
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {
    if (!QDBusConnection::sessionBus().isConnected()) {
        qDebug() << "[error] connexion dbus";
        return;
    }

    new GDBusAdaptor(this);
    QDBusConnection::sessionBus().registerObject("/", this);
    GDBusInterface* lInterface = new GDBusInterface(QString(), QString(), QDBusConnection::sessionBus(), this);

    QLineEdit* lUsernameEdit = new QLineEdit;
    m_usernameEdit = lUsernameEdit;
    lUsernameEdit->setPlaceholderText("Username");

    QPushButton* lConnect = new QPushButton;
    lConnect->setText("Connect");
    m_widgetMap[lConnect] = "connect";

    QHBoxLayout* lConnectLayout = new QHBoxLayout;
    lConnectLayout->addWidget(lUsernameEdit);
    lConnectLayout->addWidget(lConnect);
    lConnectLayout->setMargin(0);
    
    QFrame* lConnectWidget = new QFrame;
    m_connectWidget = lConnectWidget;
    lConnectWidget->setLayout(lConnectLayout);
    
    QLabel* lUsernameLabel = new QLabel;
    m_usernameLabel = lUsernameLabel;
    
    QPushButton* lDisconnect = new QPushButton;
    lDisconnect->setText("Disconnect");
    m_widgetMap[lDisconnect] = "disconnect";
    
    QHBoxLayout* lDisconnectLayout = new QHBoxLayout;
    lDisconnectLayout->addWidget(lUsernameLabel);
    lDisconnectLayout->addWidget(lDisconnect);
    lDisconnectLayout->setMargin(0);
    lDisconnectLayout->setAlignment(Qt::AlignLeft);

    QFrame* lDisconnectWidget = new QFrame;
    m_disconnectWidget = lDisconnectWidget;
    lDisconnectWidget->setLayout(lDisconnectLayout);
    lDisconnectWidget->setVisible(false);

    QLineEdit* lMessageEdit = new QLineEdit;
    m_messageEdit = lMessageEdit;
    lMessageEdit->setPlaceholderText("Message");

    QPushButton* lSend = new QPushButton;
    lSend->setText("Send");
    m_widgetMap[lSend] = "send";

    QHBoxLayout* lMessageLayout = new QHBoxLayout;
    lMessageLayout->addWidget(lMessageEdit);
    lMessageLayout->addWidget(lSend);
    lMessageLayout->setMargin(0);
    
    QFrame* lMessageWidget = new QFrame;
    m_messageWidget = lMessageWidget;
    lMessageWidget->setLayout(lMessageLayout);
    lMessageWidget->setVisible(false);

    QTextEdit* lTextEdit = new QTextEdit;
    m_textEdit = lTextEdit;
    lTextEdit->setReadOnly(true);
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addWidget(lConnectWidget);
    lMainLayout->addWidget(lDisconnectWidget);
    lMainLayout->addWidget(lMessageWidget);
    lMainLayout->addWidget(lTextEdit);

    setLayout(lMainLayout);
    
    connect(lConnect, SIGNAL(clicked()), this, SLOT(slotClick()));
    connect(lDisconnect, SIGNAL(clicked()), this, SLOT(slotClick()));
    connect(lSend, SIGNAL(clicked()), this, SLOT(slotClick()));
    connect(lInterface, SIGNAL(emitDBusMessage(QString, QString)), this, SLOT(slotDBusMessage(QString, QString)));
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
void GWindow::slotDBusMessage(const QString& key, const QString& value) {
    m_key = key;
    m_value = value;
    onEvent("dbus_message");
}
//================================================
void GWindow::updateView(const QString& event) {
    if(event == "connect") {
        m_connectWidget->setVisible(false);
        m_disconnectWidget->setVisible(true);
        m_messageWidget->setVisible(true);
    }
}
//================================================
void GWindow::onEvent(const QString& event) {
    if(event == "connect") {
        m_username = m_usernameEdit->text();
        if(m_username == "") {return;}
        updateView(event);
        m_usernameLabel->setText(m_username);
        QString lMessage = QString("<%1> vient de se connecter")
        .arg(m_username);
        emit emitDBusMessage("connect", lMessage);
    }
    else if(event == "disconnect") {
        QString lMessage = QString("<%1> vient de se déconnecter")
        .arg(m_username);
        emit emitDBusMessage("disconnect", lMessage);
        close();
    }
    else if(event == "send") {
        QString lText = m_messageEdit->text();
        if(lText == "") {return;}
        QString lMessage = QString("<%1> %2")
        .arg(m_username, lText);
        emit emitDBusMessage("message", lMessage);
    }
    else if(event == "dbus_message") {
        m_textEdit->append(m_value);
    }
}
//================================================
