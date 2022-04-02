//===============================================
#include "GObject.h"
#include "GLog.h"
#include "GFormat.h"
#include "GXml.h"
#include "GError.h"
//===============================================
GObject::GObject() {
    m_errors.reset(new GError);
}
//===============================================
GObject::~GObject() {

}
//===============================================
std::shared_ptr<GError>& GObject::getErrors() {
    return m_errors;
}
//===============================================
