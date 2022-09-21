//===============================================
#include "GObject2.h"
#include "GLog.h"
#include "GFormat.h"
#include "GCode.h"
#include "GPath.h"
//===============================================
GObject2::GObject2() {

}
//===============================================
GObject2::~GObject2() {

}
//===============================================
void GObject2::clearMap(std::vector<GObject2*>& _map) const {
    for(int i = 0; i < _map.size(); i++) {
        GObject2* lObj = _map.at(i);
        delete lObj;
    }
    _map.clear();
}
//===============================================
GString2 GObject2::serialize(const GString2& _code) const {return "";}
bool GObject2::deserialize(const GString2& _data, const GString2& _code) {return false;}
void GObject2::print() const {}
//===============================================
