//===============================================
#include "GFunction.h"
//===============================================
GFunction::GFunction() {

}
//===============================================
GFunction::~GFunction() {

}
//===============================================
sGData* GFunction::sinus(float _max, float _phase, int _size, float _range) {
    sGData* lData = (sGData*)malloc(_size*sizeof(sGData));
    for(int i = 0; i < _size; i++) {
        lData[i].x = ((float)i/_size) * _range - _range/2.0f;
        lData[i].y = _max * cosf(lData[i].x * 3.14f + _phase);
    }
    return lData;
}
//===============================================
