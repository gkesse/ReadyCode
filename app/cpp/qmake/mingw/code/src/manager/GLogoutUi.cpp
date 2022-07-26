//===============================================
#include "GLogoutUi.h"
#include "GPicto.h"
#include "GLog.h"
#include "GUser.h"
//===============================================
GLogoutUi::GLogoutUi(GUser* _user, QWidget* _parent)
: GMessageBox(_parent)
, m_user(_user) {

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
        m_user->runDisconnection();
    }
    return 0;
}
//===============================================
