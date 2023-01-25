//===============================================
#include "GProcess.h"
#include "GEnv.h"
#include "GSocket.h"
#include "GTest.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    bool lIsTestEnv = GENV->isTestEnv();
    if(lIsTestEnv) {
        runTest(_argc, _argv);
    }
    else {
        runProd(_argc, _argv);
    }
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lTest;
    lTest.run(_argc, _argv);
    m_logs.addLogs(lTest.m_logs);
}
//===============================================
void GProcess::runProd(int _argc, char** _argv) {

}
//===============================================
