//===============================================
#ifndef _GFacade_
#define _GFacade_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GFacade {
public:
    GFacade();
    ~GFacade();
    void getModule(const std::string& _dataIn, std::string& _module);
    void getMethod(const std::string& _dataIn, std::string& _method);
    void getData(const std::string& _dataIn, int _index, std::string& _data);
    void getPoint(sGPoint& _point, const std::string& _x, const std::string& _y, const std::string& _z);
};
//==============================================
#endif
//==============================================
