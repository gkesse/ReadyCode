//===============================================
#include "GMainWindow.h"
//===============================================
int main(int _argc, char** _argv) {
	QApplication app(_argc, _argv);
	QCoreApplication::setOrganizationName("IZhuravlev");
	QCoreApplication::setApplicationName("Dining Philosophers");
	QCoreApplication::setApplicationVersion("1.0");
	GMainWindow lWindow;
	lWindow.init();
	lWindow.show();
	return app.exec();
}
//===============================================
