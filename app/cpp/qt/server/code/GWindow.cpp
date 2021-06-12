//================================================
#include "GWindow.h"
//================================================
GWindow::GWindow(QWidget* parent) : QFrame(parent) {
    QPushButton* lOpen = new QPushButton;
    lOpen->setText("Open");
    m_widgetMap[lOpen] = "open";
    
    QPushButton* lNext = new QPushButton;
    lNext->setText("Next");
    m_widgetMap[lNext] = "next";
    
    QPushButton* lPrevious = new QPushButton;
    lPrevious->setText("Previous");
    m_widgetMap[lPrevious] = "previous";
    
    QHBoxLayout* lButtonLayout = new QHBoxLayout;
    lButtonLayout->addWidget(lOpen);
    lButtonLayout->addWidget(lPrevious);
    lButtonLayout->addWidget(lNext);
    lButtonLayout->setAlignment(Qt::AlignLeft);
    lButtonLayout->setMargin(0);
    
    QTextEdit* lTextedit = new QTextEdit;
    m_textEdit = lTextedit;
    lTextedit->setReadOnly(true);
    
    QVBoxLayout* lMainLayout = new QVBoxLayout;
    lMainLayout->addLayout(lButtonLayout);
    lMainLayout->addWidget(lTextedit, 1);
    
    setLayout(lMainLayout);
    
    connect(lOpen, SIGNAL(clicked()), this, SLOT(slotClick()));
    connect(lNext, SIGNAL(clicked()), this, SLOT(slotClick()));
    connect(lPrevious, SIGNAL(clicked()), this, SLOT(slotClick()));
}
//================================================
GWindow::~GWindow() {

}
//================================================
void GWindow::onEvent(const QString& event) {
    if(event == "open") {
        QString lFilename = QFileDialog::getOpenFileName(
        this, tr("Ouvrir une image"), ".", tr("Fichiers Image (*.png *.jpg *.bmp)"));
        if(lFilename == "") {return;}
        m_textEdit->append(lFilename);
        m_filename = lFilename;
    }
    else if(event == "next") {
        if(m_filename == "") {return;}
        QFileInfo lFileInfo(m_filename);
        QDir lDir = lFileInfo.absoluteDir();
        QStringList lFilters;
        lFilters << "*.png" << "*.bmp" << "*.jpg";
        QStringList lFilenames = lDir.entryList(lFilters, QDir::Files, QDir::Name);
        int lIndex = lFilenames.indexOf(QRegExp(QRegExp::escape(lFileInfo.fileName())));
        if(lIndex < lFilenames.size() - 1) {
            QString lFilename = lDir.absoluteFilePath(lFilenames.at(lIndex + 1));
            m_textEdit->append(lFilename);
            m_filename = lFilename;
        } else {
            m_textEdit->append("Cette image est la dernière...");
        }    
    }
    else if(event == "previous") {
        if(m_filename == "") {return;}
        QFileInfo lFileInfo(m_filename);
        QDir lDir = lFileInfo.absoluteDir();
        QStringList lFilters;
        lFilters << "*.png" << "*.bmp" << "*.jpg";
        QStringList lFilenames = lDir.entryList(lFilters, QDir::Files, QDir::Name);
        int lIndex = lFilenames.indexOf(QRegExp(QRegExp::escape(lFileInfo.fileName())));
        if(lIndex > 0) {
            QString lFilename = lDir.absoluteFilePath(lFilenames.at(lIndex - 1));
            m_textEdit->append(lFilename);
            m_filename = lFilename;
        } else {
            m_textEdit->append("Cette image est la première...");
        }    
    }
}
//================================================
void GWindow::slotClick() {
    QWidget* lWidget = qobject_cast<QWidget*>(sender());
    QString lWidgetId = m_widgetMap[lWidget];
    onEvent(lWidgetId);
}
//================================================