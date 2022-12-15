//===============================================
#include "GPocoRequest.h"
#include "GLog.h"
//===============================================
GPocoRequest::GPocoRequest() {

}
//===============================================
GPocoRequest::~GPocoRequest() {

}
//===============================================
void GPocoRequest::handleRequest(Poco::Net::HTTPServerRequest& _request, Poco::Net::HTTPServerResponse& _response) {
    GLOGT(eGFUN, "");
    _response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    _response.setContentType("text/html");
    std::ostream& out = _response.send();
    out     << "<h1>Hello world!</h1>"
            << "<p>Host: "   << _request.getHost()   << "</p>"
            << "<p>Method: " << _request.getMethod() << "</p>"
            << "<p>URI: "    << _request.getURI()    << "</p>";
    out.flush();

    std::cout << std::endl
            << "Response sent for count=" << 1
            << " and URI=" << _request.getURI() << std::endl;
}
//===============================================
