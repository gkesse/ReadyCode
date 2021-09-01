//===============================================
#include "GBoostUi.h"
//===============================================
GBoostUi::GBoostUi(QObject* parent) :
QObject(parent) {

}
//===============================================
GBoostUi::~GBoostUi() {

}
//===============================================
GBoostUi* GBoostUi::Create(const QString& key) {
	if(key == "default") {return new GBoostUi;}
	// default
	return new GBoostUi;
}
//===============================================
void GBoostUi::run(int argc, char** argv) {
	const int BACKLOG_SIZE = 30;
	unsigned short port_num = 3333;
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::any(), port_num);
	boost::asio::io_service ios;

	try {
		boost::asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
		acceptor.bind(ep);
		acceptor.listen(BACKLOG_SIZE);
		boost::asio::ip::tcp::socket sock(ios);
		acceptor.accept(sock);
		// code d'envoi et de reception de donnees
	}
	catch (boost::system::system_error &e) {
		std::cout
		<< "Error occured! Error code = " << e.code()
		<< ". Message: " << e.what() << std::endl;
	}
}
//===============================================
