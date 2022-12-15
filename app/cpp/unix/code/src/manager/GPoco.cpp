//===============================================
#include "GPoco.h"
#include "GLog.h"
//===============================================
GPoco::GPoco(const GString& _code)
: GObject(_code) {

}
//===============================================
GPoco::~GPoco() {

}
//===============================================
bool GPoco::doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response) {
    session.sendRequest(request);
    std::istream& rs = session.receiveResponse(response);
    std::cout << response.getStatus() << " " << response.getReason() << std::endl;
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED) {
        Poco::StreamCopier::copyStream(rs, std::cout);
        return true;
    }
    else {
        Poco::NullOutputStream null;
        Poco::StreamCopier::copyStream(rs, null);
        return false;
    }
    return true;
}
//===============================================
bool GPoco::doGet(const GString& _uri) {
    try {
        Poco::URI uri(_uri.c_str());
        GString path(uri.getPathAndQuery());
        if (path.isEmpty()) path = "/";

        std::string username;
        std::string password;
        Poco::Net::HTTPCredentials::extractCredentials(uri, username, password);
        Poco::Net::HTTPCredentials credentials(username, password);

        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path.c_str(), Poco::Net::HTTPMessage::HTTP_1_1);
        Poco::Net::HTTPResponse response;

        if (!doRequest(session, request, response)) {
            credentials.authenticate(request, response);
            if (!doRequest(session, request, response)) {
                GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête.");
                return false;
            }
        }
    }
    catch(Poco::Exception& e) {
        GERROR_ADD(eGERR, "Erreur lors de l'exécution de la requête.\n%s", e.displayText().c_str());
        return false;
    }
    return true;
}
//===============================================
