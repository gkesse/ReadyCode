//===============================================
#include "GStruct.h"
//===============================================
sGPoint::sGPoint() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
}
//===============================================
sGPoint::sGPoint(float _x, float _y) {
    x = _x;
    y = _y;
    z = 0.f;
}
//===============================================
sGPoint::sGPoint(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}
//===============================================
sGPoint::sGPoint(const sGPoint& _p) {
    x = _p.x;
    y = _p.y;
    z = _p.z;
}
//===============================================
sGPoint& sGPoint::operator*=(const sGPoint& _p) {
    x *= _p.x;
    y *= _p.y;
    z *= _p.z;
    return *this;
}
//===============================================
sGPoint operator*(const sGPoint& _p1, const sGPoint& _p2) {
    sGPoint p(_p1);
    p *= _p2;
    return p;
}
//===============================================
sGPoint& sGPoint::operator/=(const sGPoint& _p) {
    x /= _p.x;
    y /= _p.y;
    z /= _p.z;
    return *this;
}
//===============================================
sGPoint operator/(const sGPoint& _p1, const sGPoint& _p2) {
    sGPoint p(_p1);
    p /= _p2;
    return p;
}
//===============================================
sGColor::sGColor() {
    r = 0.f;
    g = 0.f;
    b = 0.f;
    a = 1.f;
}
//===============================================
sGColor::sGColor(float _r, float _g, float _b) {
    r = _r;
    g = _g;
    b = _b;
    a = 1.f;
}
//===============================================
sGColor::sGColor(float _r, float _g, float _b, float _a) {
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}
//===============================================
sGColor::sGColor(const sGColor& _c) {
    r = _c.r;
    g = _c.g;
    b = _c.b;
    a = _c.a;
}
//===============================================
sGVertex::sGVertex() {

}
//===============================================
sGVertex::sGVertex(const sGPoint& _d, const sGColor& _c) {
    d = _d;
    c = _c;
}
//===============================================
sGVertex::sGVertex(const sGVertex& _v) {
    d = _v.d;
    c = _v.c;
}
//===============================================
sGRange::sGRange() {
    m_min = 0.f;
    m_max = 0.f;
}
//===============================================
sGRange::sGRange(float _min, float _max) {
    m_min = _min;
    m_max = _max;
}
//===============================================
sGRange::sGRange(const sGRange& _r) {
    m_min = _r.m_min;
    m_max = _r.m_max;
}
//===============================================
sGRange& sGRange::operator+=(float _r) {
    m_min += _r;
    m_max += _r;
    return *this;
}
//===============================================
sGRange operator+(const sGRange& _r1, float _r2) {
    sGRange r(_r1);
    r += _r2;
    return r;
}
//===============================================
sGRange& sGRange::operator-=(float _r) {
    m_min -= _r;
    m_max -= _r;
    return *this;
}
//===============================================
sGRange operator-(const sGRange& _r1, float _r2) {
    sGRange r(_r1);
    r -= _r2;
    return r;
}
//===============================================
sGGrid::sGGrid() {
    width = 0.f;
    height = 0.f;
    gridWidth = 0.f;
    axisWidth = 0.f;
    pointsize = 0.f;
}
//===============================================
sGOpenGL::sGOpenGL() {
	point = {5.f, 5.f, 0.f};
}
//===============================================
sGSocket::sGSocket() {
    address_ip = "0.0.0.0";
    port = 8585;
    backlog = 10;
    major = 2;
    minor = 2;
    on_start = 0;
    socket = 0;
    hostname_on = false;
}
//===============================================
sGMaster::sGMaster() {
    run = true;
}
//===============================================
