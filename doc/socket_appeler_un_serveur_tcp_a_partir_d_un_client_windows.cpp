// appel du serveur
bool GSocket::callServer() {
    WSADATA lWsaData;
    WSAStartup(MAKEWORD(m_major, m_minor), &lWsaData);
    m_socket = socket(m_domain, m_type, m_protocol);
    if(m_socket == INVALID_SOCKET) {GERROR_ADD(eGERR, "Erreur lors de la connexion au serveur."); return false;}
    SOCKADDR_IN lAddress;
    lAddress.sin_family = m_family;
    lAddress.sin_addr.s_addr = inet_addr(m_hostname.c_str());
    lAddress.sin_port = htons(m_port);
    memset(&lAddress.sin_zero, 0, sizeof(lAddress.sin_zero));
    int lAnswer = connect(m_socket, (SOCKADDR*)(&lAddress), sizeof(lAddress));
    if(lAnswer == SOCKET_ERROR) {GERROR_ADD(eGERR, "Erreur lors de la connexion au serveur."); return false;}

    m_dataOut = "";
    m_dataIn = "";

    if(createData()) {
        if(sendData()) {
            if(readMethod()) {
                onCallServer();
            }
        }
    }

    GLOGT(eGMSG, "[EMISSION] : (%d)\n%s", (int)m_dataOut.size(), m_dataOut.c_str());
    GLOGT(eGMSG, "[RECEPTION] : (%d)\n%s", (int)m_dataIn.size(), m_dataIn.c_str());

    closesocket(m_socket);
    WSACleanup();
    return true;
}

// envoi des donnees
bool GSocket::sendData() {
    int lIndex = 0;
    int lSize = m_dataOut.size();
    const char* lBuffer = m_dataOut.c_str();

    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes <= 0) return false;
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }

    return true;
}

// boucle de reception des donnees
bool GSocket::readData(int _diffSize) {
    if(_diffSize < 0) return false;
    if(_diffSize == 0) return true;
    char lBuffer[BUFFER_SIZE + 1];
    int lSize = 0;
    while(1) {
        int lBytes = readData(lBuffer, BUFFER_SIZE);
        if(lBytes <= 0) return false;
        lBuffer[lBytes] = 0;
        m_dataIn += lBuffer;
        lSize += lBytes;
        if(lSize >= _diffSize) return true;
    }
    return true;
}

// reception de donnees
int GSocket::readData(char* _data, int _size) {
    int lBytes = recv(m_socket, _data, _size, 0);
    return lBytes;
}
