//===============================================
#include "GTimer.h"
//===============================================
GTimer::GTimer() {

}
//===============================================
GTimer::~GTimer() {

}
//===============================================
void GTimer::delayMs(int _ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(_ms));
}
//===============================================