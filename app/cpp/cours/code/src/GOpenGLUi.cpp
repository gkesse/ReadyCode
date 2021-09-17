//===============================================
#include "GOpenGLUi.h"
//===============================================
GOpenGLUi::GOpenGLUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GOpenGLUi::~GOpenGLUi() {

}
//===============================================
GOpenGLUi* GOpenGLUi::Create(const QString& key) {
	if(key == "default") {return new GOpenGLUi;}
	// default
	return new GOpenGLUi;
}
//===============================================
void GOpenGLUi::run(int argc, char** argv) {}
//===============================================
