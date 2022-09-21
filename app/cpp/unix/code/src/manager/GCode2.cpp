//===============================================
#include "GCode2.h"
#include "GLog.h"
#include "GFormat.h"
//===============================================
GCode2::GCode2()
: GXml2() {

}
//===============================================
GCode2::~GCode2() {

}
//===============================================
bool GCode2::createCode() {
    if(!getNode("/rdv/datas")) {
        createNodePath("/rdv/datas");
    }
    return true;
}
//===============================================
bool GCode2::createCode(const GString2& _code) {
    if(!getNode(sformat("/rdv/datas/data[code='%s']", _code.c_str()))) {
        createCode();
        createNode("data");
        next();
        createNode("code");
        next();
        setValue(_code);
    }
    return true;
}
//===============================================
