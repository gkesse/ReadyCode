//===============================================
#include "GSQLitePage.h"
#include "GManager.h"
#include "GDialogUi.h"
//===============================================
GSQLitePage::GSQLitePage(QWidget* parent) :
GProUi(parent) {
    QTextEdit* lTextEdit = new QTextEdit;
    m_textEdit = lTextEdit;
    lTextEdit->setReadOnly(true);
    lTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    lTextEdit->setStyleSheet(QString(""
            "QTextEdit {"
            "border:none;"
            "background-color:black;"
            "color:white;"
            "font-family:courier;"
            "}"
            ""));

    QPushButton* lMasterButton = new QPushButton;
    lMasterButton->setText("Master");
    m_widgetMap[lMasterButton] = "master";

    QPushButton* lTablesButton = new QPushButton;
    lTablesButton->setText("Tables");
    m_widgetMap[lTablesButton] = "tables";

    QPushButton* lTableButton = new QPushButton;
    lTableButton->setText("Table");
    m_widgetMap[lTableButton] = "table";

    QPushButton* lSchemaButton = new QPushButton;
    lSchemaButton->setText("Schema");
    m_widgetMap[lSchemaButton] = "schema";

    QPushButton* lUpdateButton = new QPushButton;
    lUpdateButton->setText("Modifier");
    m_widgetMap[lUpdateButton] = "update";

    QPushButton* lDeleteButton = new QPushButton;
    lDeleteButton->setText("Supprimer");
    m_widgetMap[lDeleteButton] = "delete";

    QVBoxLayout* lButtonLayout = new QVBoxLayout;
    lButtonLayout->addWidget(lMasterButton);
    lButtonLayout->addWidget(lTablesButton);
    lButtonLayout->addWidget(lTableButton);
    lButtonLayout->addWidget(lSchemaButton);
    lButtonLayout->addWidget(lUpdateButton);
    lButtonLayout->addWidget(lDeleteButton);
    lButtonLayout->setAlignment(Qt::AlignTop);
    lButtonLayout->setMargin(0);

    // layout
    QHBoxLayout* lMainLayout = new QHBoxLayout;
    lMainLayout->addWidget(lTextEdit);
    lMainLayout->addLayout(lButtonLayout);

    setLayout(lMainLayout);

    connect(lMasterButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lTablesButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lTableButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lSchemaButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lUpdateButton, SIGNAL(clicked()), this, SLOT(onEvent()));
    connect(lDeleteButton, SIGNAL(clicked()), this, SLOT(onEvent()));
}
//===============================================
GSQLitePage::~GSQLitePage() {

}
//===============================================
void GSQLitePage::onEvent() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];
    onEvent(lWidgetId);
}
//===============================================
void GSQLitePage::onEvent(const QString& text) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    if(text == "master") {
        GManager::Instance()->runCmd(QString("bash %1").arg(lApp->sqlite_sql_master));
        m_textEdit->setText("L'opération a été réalisée avec succès...");
    }
    else if(text == "tables") {
        QVector<QString> lTables = GManager::Instance()->getTables();
        GManager::Instance()->setData2(m_textEdit, lTables);
    }
    else if(text == "table") {
        GDialogUi* lTableUi = GDialogUi::Create("sqlite/table/show", this);
        int lOk = lTableUi->exec();
        if(lOk == QDialog::Rejected) {delete lTableUi; return;}
        QString lTable = lTableUi->getData().value("table");
        if(lTable == "") {delete lTableUi; return;}
        QVector<QVector<QString>> lData = GManager::Instance()->getData(lTable);
        GManager::Instance()->setData(m_textEdit, lData);
        delete lTableUi;
    }
    else if(text == "schema") {
        GDialogUi* lSchemaUi = GDialogUi::Create("sqlite/schema/show", this);
        int lOk = lSchemaUi->exec();
        if(lOk == QDialog::Rejected) {delete lSchemaUi; return;}
        QString lTable = lSchemaUi->getData().value("table");
        if(lTable == "") {delete lSchemaUi; return;}
        QString lSchema = GManager::Instance()->getSchema(lTable);
        m_textEdit->setText(lSchema.toUpper());
        delete lSchemaUi;
    }
    else if(text == "update") {
        QStringList lFilters = QStringList() << "*.sh";
        QStringList lFiles = GManager::Instance()->getDirFiles(lApp->sqlite_sql_path, lFilters);
        m_textEdit->clear();
        for(int i = 0; i < lFiles.size(); i++) {
            QString lFile = lFiles.at(i);
            QString lFilename = QFileInfo(lFile).baseName();
            QString lFileId = lFilename.split('_').first();
            int lCount = GManager::Instance()->countFileId(lFileId);
            if(lCount == 0) {
                GManager::Instance()->runCmd(QString("bash %1").arg(lFile));
                GManager::Instance()->insertFileId(lFileId);
                m_textEdit->append(QString("%1 : %2").arg(lFileId).arg(lFile));
            }
        }
    }
    else if(text == "delete") {
        GDialogUi* lDeleteUi = GDialogUi::Create("sqlite/table/delete", this);
        int lOk = lDeleteUi->exec();
        if(lOk == QDialog::Rejected) {delete lDeleteUi; return;}
        QString lTable = lDeleteUi->getData().value("table");
        if(lTable == "") {delete lDeleteUi; return;}
        GManager::Instance()->deleteTable(lTable);
        delete lDeleteUi;
        m_textEdit->setText("L'opération a été réalisée avec succès...");
    }
}
//===============================================
void GSQLitePage::setTitle() {
    setWindowTitle("ReadyApp | SQLite");
}
//===============================================
