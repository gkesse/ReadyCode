// detection de la methode
bool GServer::onRunServerTcp() {
    if(m_dataIn.startBy(m_apiMethod)) {
        onReadyApp();
    }
    else if(m_dataIn.startBy("GET")) {
        onHttpApp();
    }
    return true;
}

// analyse de la requete
bool GServer::onHttpApp() {
    GHttp lHttp;
    lHttp.setServer(this);
    lHttp.runHttp();
    return true;
}

void GHttp::runHttp() {
    analyzeHeader();
    analyzeMethod();
}

// analyse de la l'entete de la requete
bool GHttp::analyzeHeader() {
    int lIndex = 0;
    GString lLine = "";
    GString& lDataIn = m_server->getDataIn();

    for(int i = 0; i < lDataIn.size(); i++) {
        char lChar = lDataIn[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            GString lMethod = lLine.extract(0, " \r\n").trim();
            GString lUrl = lLine.extract(1, " \r\n").trim();
            GString lVersion = lLine.extract(2, " \r\n").trim();
            setMethod(lMethod);
            setUrl(lUrl);
            setVersion(lVersion);
            lLine = "";
            break;
        }
    }
    for(int i = 0; i < lDataIn.size(); i++) {
        char lChar = lDataIn[i];
        lLine += lChar;
        if(isLine(lChar, lIndex)) {
            if(lLine.startBy("Host")) {
                GString lHostname = lLine.extract(1, ":\r\n").trim();
                GString lPort = lLine.extract(2, ":\r\n").trim();
                setHostname(lHostname);
                setPort(lPort.toInt());
            }
            else if(lLine.startBy("Connection")) {
                GString lConnection = lLine.extract(1, ":\r\n").trim();
                setConnection(lConnection);
            }
            else if(lLine.startBy("Cache-Control")) {
                GString lCacheControl = lLine.extract(1, ":\r\n").trim();
                setCacheControl(lCacheControl);
            }
            else if(lLine.startBy("Upgrade-Insecure-Requests")) {
                GString lUpgradeInsecureRequests = lLine.extract(1, ":\r\n").trim();
                setUpgradeInsecureRequests(lUpgradeInsecureRequests);
            }
            else if(lLine.startBy("User-Agent")) {
                GString lUserAgent = lLine.extract(1, ":\r\n").trim();
                setUserAgent(lUserAgent);
            }
            else if(lLine.startBy("Accept")) {
                GString lAccept = lLine.extract(1, ":\r\n").trim();
                setAccept(lAccept);
            }
            else if(lLine.startBy("Accept-Encoding")) {
                GString lAcceptEncoding = lLine.extract(1, ":\r\n").trim();
                setAcceptEncoding(lAcceptEncoding);
            }
            else if(lLine.startBy("Accept-Language")) {
                GString lAcceptLanguage = lLine.extract(1, ":\r\n").trim();
                setAcceptLanguage(lAcceptLanguage);
            }
            lLine = "";
        }
    }
    return true;
}

// selection de la methode
bool GHttp::analyzeMethod() {
    if(m_method == "GET") {
        analyzeGet();
    }
    else if(m_method == "POST") {
        analyzePost();
    }
    return true;
}

// selection de la ressource
bool GHttp::analyzeGet() {
    if(m_url == "/") {
        onGetIndex();
    }
    return true;
}

// execution de la requete
void GHttp::onGetIndex() {
    setVersion("HTTP/1.1");
    setStatus(200);
    setReason("OK");
    setContentType("text/html");
    setConnection("Closed");

    GString lContent = ""
            "<html><head><title>[Echo]-ReadyDev</title></head>"
            "<body><h1>La connexion au serveur a réussi.</h1></body></html>"
            "";

    setContent(lContent);
    createGetData();
}

// preparation de la reponse
bool GHttp::createGetData() {
    if(m_version == "") return false;
    if(m_status == 0) return false;
    if(m_reason == "") return false;
    if(m_content == "") return false;
    if(m_contentType == "") return false;
    if(m_contentLength == 0) return false;

    GString& lDataOut = m_server->getDataOut();
    lDataOut += GFORMAT("%s %d %s\r\n", m_version.c_str(), m_status, m_reason.c_str());
    lDataOut += GFORMAT("Content-Type: %s\r\n", m_contentType.c_str());
    lDataOut += GFORMAT("Content-Length: %d\r\n", m_contentLength);

    if(m_connection != "") {
        lDataOut += GFORMAT("Connection: %s\r\n", m_connection.c_str());
    }

    lDataOut += GFORMAT("\r\n");
    lDataOut += GFORMAT("%s", m_content.c_str());
    return true;
}
