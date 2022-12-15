//===============================================
#include "GPocoServerApp.h"
#include "GPocoRequestFactory.h"
#include "GLog.h"
//===============================================
int GPocoServerApp::main(const std::vector<std::string>& _args) {
    GLOGT(eGFUN, "");
    Poco::Net::HTTPServer lServer(new GPocoRequestFactory, Poco::Net::ServerSocket(9080), new Poco::Net::HTTPServerParams);
    lServer.start();
    std::cout << std::endl << "Server started" << std::endl;
    waitForTerminationRequest();  // wait for CTRL-C or kill
    std::cout << std::endl << "Shutting down..." << std::endl;
    lServer.stop();
    return Application::EXIT_OK;
}
//===============================================
