//===============================================
#include "GLogoutUi.h"
#include "GPicto.h"
#include "GLog.h"
#include "GConnection.h"
//===============================================
GLogoutUi::GLogoutUi(GConnection* _connection, QWidget* _parent)
: GMessageBox(_parent)
, m_connection(_connection) {

}
//===============================================
GLogoutUi::~GLogoutUi() {

}
//===============================================
int GLogoutUi::exec() {
    setWindowTitle("Déconnexion");
    setIcon(QMessageBox::Question);
    setText("Voulez-vous vous déconnecter ?");
    QAbstractButton* lYesButton = addButton(tr("Oui"), QMessageBox::YesRole);
    addButton(tr("Non"), QMessageBox::NoRole);
    GMessageBox::exec();
    if(clickedButton() == lYesButton) {
        m_connection->runDisconnection();
    }
    return 0;
}
//===============================================
