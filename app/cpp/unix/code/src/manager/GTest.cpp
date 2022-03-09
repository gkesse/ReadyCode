//===============================================
#include "GTest.h"
#include "GPath.h"
#include "GXml.h"
#include "GFormat.h"
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
	else if(lKey == "xml") {
		runXml(_argc, _argv);
	}
	else {
		runTest(_argc, _argv);
	}
}
//===============================================
void GTest::runTest(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	std::string lPath = GRES("xml", "app.xml");
	printf("%s\n", lPath.c_str());
}
//===============================================
void GTest::runPath(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	std::string lPath = GRES("xml", "pad.xml");
	printf("%s\n", lPath.c_str());
}
//===============================================
void GTest::runXml(int _argc, char** _argv) {
	printf("%s\n", __FUNCTION__);
	m_dom.reset(new GXml);
	m_dom->loadXmlFile(GRES("xml", "pad.xml"));
	m_dom->createXPath();
	printf("%s : %s\n", "app_name", getPadItem("app_name").c_str());
}
//===============================================
std::string GTest::getPadItem(const std::string& _data) const {
    m_dom->queryXPath(GFORMAT->sformat("/rdv/datas/data[code='pad']/%s", _data.c_str()));
    m_dom->getNodeXPath();
    std::string lData = m_dom->getNodeValue();
    return lData;
}
//===============================================
