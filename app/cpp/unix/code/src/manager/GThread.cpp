//===============================================
#include "GThread.h"
#include "GPath.h"
#include "GXml.h"
#include "GFormat.h"
#include "GSocket.h"
#include "GFile.h"
//===============================================
GThread::GThread() : GObject() {

}
//===============================================
GThread::~GThread() {

}
//===============================================
void GThread::createThread(void* _onThread, void* _params) {
    m_thread.thread(_onThread, _params);
}
//===============================================
