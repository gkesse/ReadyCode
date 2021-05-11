//================================================
#include "GWindow.h"
//================================================
GWindow::GWindow(QWidget* parent) : QMainWindow(parent) {
    QMenu* lMenu;
    QAction* lAction;
        
    lMenu = menuBar()->addMenu("Fichier");
    //
    lAction = new QAction;
    lAction->setText("Ajouter des données");
    lAction->setData("add_data");
    lMenu->addAction(lAction);
    connect(lAction, SIGNAL(triggered()), this, SLOT(onClick()));
    //
    lAction = new QAction;
    lAction->setText("Sauvegarder les données");
    lAction->setData("save_data");
    lMenu->addAction(lAction);
    connect(lAction, SIGNAL(triggered()), this, SLOT(onClick()));
    
    QTextEdit* lTextEdit = new QTextEdit;
    m_textEdit = lTextEdit;
    lTextEdit->setReadOnly(true);
    
    setCentralWidget(lTextEdit);
    
    loadData();
}
//================================================
GWindow::~GWindow() {
    
}
//================================================
void GWindow::onClick() {
    QAction* lAction  = qobject_cast<QAction*>(sender());
    QString lKey = lAction->data().toString();
    
    if(lKey == "add_data") {
        addData();
    }
    else if(lKey == "save_data") {
        saveData();
    }
}
//================================================
void GWindow::loadData() {
    QFile lFile("user.dat");

    m_index = 0;
    if (!lFile.open(QIODevice::ReadOnly)) {return;}

    QDataStream in(&lFile);
    in >> m_userMap;
    m_index = m_userMap.size();
    showData();
}
//================================================
void GWindow::saveData() {
    QFile lFile("user.dat");

    if (!lFile.open(QIODevice::WriteOnly)) {return;}

    QDataStream out(&lFile);
    out << m_userMap;
}
//================================================
void GWindow::showData() {
    m_textEdit->clear();
    for(int i = 0; i < m_userMap.size(); i++) {
        sGUser lUser = m_userMap[i];
        QString lText = QString("%1 ; %2 ; %3"
        ).arg(lUser.id).arg(lUser.name).arg(lUser.email);
        m_textEdit->append(lText);
    }
}
//================================================
void GWindow::addData() {
    sGUser lUser;
    m_index += 1;
    lUser.id = m_index;
    lUser.name = QString("Gerard KESSE");
    lUser.email = QString("contact@readydev.com");
    m_userMap.push_back(lUser);
    showData();
}
//================================================
