//===============================================
#include "GSocketServer.h"
#include "GFile2.h"
#include "GString.h"
#include "GSocket.h"
//===============================================
GSocketServer::GSocketServer() {

}
//===============================================
GSocketServer::~GSocketServer() {

}
//===============================================
void GSocketServer::run(int argc, char** argv) {
    const int BUFFER_SIZE = 1024;
    char lBuffer[BUFFER_SIZE + 1];

    int lSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in lAddress;
    bzero(&lAddress, sizeof(lAddress));
    lAddress.sin_family = AF_INET;
    lAddress.sin_addr.s_addr = INADDR_ANY;
    lAddress.sin_port = htons(8585);
    bind(lSocket, (struct sockaddr*)&lAddress, sizeof(lAddress));
    listen(lSocket, 5);
    struct sockaddr_in lAddress2;
    socklen_t lAdresseSize2 = sizeof(lAddress2);

    while(1) {
        int lSocket2 = accept(lSocket, (struct sockaddr*)&lAddress2, &lAdresseSize2);
        int lBytes = read(lSocket2, lBuffer, BUFFER_SIZE);
        GString lFilename;
        lFilename.setData(lBuffer, lBytes);
        printf("Reading file %s\n", lFilename.c_str());
        GFile2 lFile;
        lFile.setFilename(lFilename.c_str());
        lFile.openFile2();
        GString lData;
        lFile.readAll(lData);
        lFile.closeFile();
        int lIndex = 0;

        while(1) {
        	lBytes = lData.toChar(lBuffer, lIndex, BUFFER_SIZE);
            if(lBytes <= 0) {break;}
            std::cout << lBytes << "...\n";
            lBuffer[lBytes] = 0;
            write(lSocket2, lBuffer, lBytes);
            lIndex += lBytes;
        }

        close(lSocket2);
    }

    close (lSocket);
}
//===============================================
