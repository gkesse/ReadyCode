//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
class GManager {
public:
    GManager();
    ~GManager();
    void createPoint(std::string& _data, const std::string& _x, const std::string& _y, const std::string& _z);
    void callServer(const std::string& _dataIn, std::string& _dataOut);
    void startServer(sGSocket& _socket);
    void startServer(void* _onStart);
    bool isEmpty(QTextEdit* _textEdit);
    void getData(QTextEdit* _textEdit, std::string& _data);
    void getKey(int _argc, char** _argv, int _index, QString& _key);
};
//==============================================
#endif
//==============================================
