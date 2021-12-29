//===============================================
#include "GQtObject.h"
//===============================================
GQtObject::GQtObject(QObject* _parent) :
QObject(_parent) {
    m_dataPath = "C:/Users/Admin/Downloads/Programs/ReadyData/data/studio";
}
//===============================================
GQtObject::~GQtObject() {

}
//===============================================
QString GQtObject::getDataPath() {
    return m_dataPath;
}
//===============================================
