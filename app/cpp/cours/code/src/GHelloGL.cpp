//===============================================
#include "GHelloGL.h"
#include "GHelloGLWidget.h"
#include "GHelloGLDock.h"
//===============================================
GHelloGL::GHelloGL(QWidget* parent) : GQtUi(parent) {
	QCoreApplication::setApplicationName("ReadyApp");
	QCoreApplication::setOrganizationName("ReadyDev");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);

	QCommandLineParser parser;
	parser.setApplicationDescription(QCoreApplication::applicationName());
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption multipleSampleOption("multisample", "Multisampling");
	parser.addOption(multipleSampleOption);
	QCommandLineOption coreProfileOption("coreprofile", "Use core profile");
	parser.addOption(coreProfileOption);
	QCommandLineOption transparentOption("transparent", "Transparent window");
	parser.addOption(transparentOption);

	parser.process(*qApp);

	QSurfaceFormat fmt;
	fmt.setDepthBufferSize(24);
	//if (parser.isSet(multipleSampleOption)) {
	fmt.setSamples(4);
	//}
	//if (parser.isSet(coreProfileOption)) {
	fmt.setVersion(3, 2);
	fmt.setProfile(QSurfaceFormat::CoreProfile);
	//}
	QSurfaceFormat::setDefaultFormat(fmt);

	mainWindow = new QMainWindow;

	QMenuBar *menuBar = new QMenuBar;
	QMenu *menuWindow = menuBar->addMenu(tr("&Window"));
	QAction *addNew = new QAction(menuWindow);
	addNew->setText(tr("Add new"));
	menuWindow->addAction(addNew);
	connect(addNew, SIGNAL(triggered()), this, SLOT(onAddNew()));
	mainWindow->setMenuBar(menuBar);

	QVBoxLayout* lMainLayout = new QVBoxLayout;
	lMainLayout->addWidget(mainWindow);

	setLayout(lMainLayout);

	GHelloGLWidget::setTransparent(parser.isSet(transparentOption));
	if (GHelloGLWidget::isTransparent()) {
		setAttribute(Qt::WA_TranslucentBackground);
		setAttribute(Qt::WA_NoSystemBackground, false);
	}
}
//===============================================
GHelloGL::~GHelloGL() {

}
//===============================================
void GHelloGL::resize() {
	QFrame::resize(400, 350);
}
//===============================================
QMainWindow* GHelloGL::getWindow() {
	return mainWindow;
}
//===============================================
void GHelloGL::onAddNew() {
	if (!mainWindow->centralWidget()) {
		mainWindow->setCentralWidget(new GHelloGLDock(mainWindow));
	}
	else {
		QMessageBox::information(nullptr, tr("Cannot add new window"),
				tr("Already occupied. Undock first."));
	}
}
//===============================================
