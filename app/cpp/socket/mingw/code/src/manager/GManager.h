//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
//===============================================
#define GMGR GManager::Instance()
//===============================================
class GManager {
public:
	GManager();
	~GManager();
	static GManager* Instance();
	void getModule(const std::string& _dataIn, std::string& _module);
	void getMethod(const std::string& _dataIn, std::string& _method);
	void getData(const std::string& _dataIn, int _index, std::string& _data);
	void getPoint(sGPoint& _point, const std::string& _x, const std::string& _y, const std::string& _z);
	void callServer(const std::string& _dataIn, std::string& _dataOut);
	void startServer(sGSocket& _socket);
	void startServer(void* _onStartServer);
	void onStartServer(void* _params, std::queue<std::string>& _data);

private:
	static GManager* m_instance;
};
//==============================================
#endif
//==============================================
