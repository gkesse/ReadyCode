//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GFormat.h"
#include "GSocket.h"
//===============================================
GTest::GTest() : GObject() {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run(int _argc, char** _argv) {
	std::string lKey = "default";
	if(_argc > 2) lKey = _argv[2];

	if(lKey == "default") {
		runTest(_argc, _argv);
	}
	else if(lKey == "path") {
		runPath(_argc, _argv);
	}
	else if(lKey == "format") {
		runFormat(_argc, _argv);
	}
	else if(lKey == "xml") {
		runXml(_argc, _argv);
	}
	else if(lKey == "socket/server") {
		runSocketServer(_argc, _argv);
	}
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	std::string lPath = GRES("xml", "pad.xml");
	printf("%s\n", lPath.c_str());
}
//===============================================
void GTest::runFormat(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	printf("%s\n", sformat("app : %s - v%s", "ReadyPad", "1.0").c_str());
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	m_dom.reset(new GXml);
	m_dom->loadXmlFile(GRES("xml", "pad.xml"));
	m_dom->createXPath();
	printf("app_name......: %s\n", getPadItem("app_name").c_str());
	printf("app_version...: %s\n", getPadItem("app_version").c_str());
}
//===============================================
std::string GTest::getPadItem(const std::string& _data) const {
    m_dom->queryXPath(sformat("/rdv/datas/data[code='pad']/%s", _data.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
void GTest::runSocketServer(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	GSocket lServer;
	GSocket lClient;

	int lDomain = lServer.loadDomain();
	int lType = lServer.loadType();
	int lProtocol = lServer.loadProtocol();
	int lFamily = lServer.loadFamily();
	std::string lClientIp = lServer.getSocketItem("client_ip");
	int lPort = std::stoi(lServer.getSocketItem("port"));
	int lBacklog = std::stoi(lServer.getSocketItem("backlog"));

	lServer.createSocket(lDomain, lType, lProtocol);
	lServer.createAddress(lFamily, lClientIp, lPort);
	lServer.bindSocket();
	lServer.listenSocket(lBacklog);
	lServer.start();
	lServer.acceptSocket(lClient);

	std::string lData;
	lClient.recvData(lData);
	printf("[server] : %s\n", lData.c_str());
}
//===============================================
