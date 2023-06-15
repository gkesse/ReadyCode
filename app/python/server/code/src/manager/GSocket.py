#================================================
from functions import *
from manager.GObject import GObject
#================================================
class GSocket(GObject):
    #================================================
    BUFFER_SIZE = 1024
    #================================================
    def __init__(self):
        GObject.__init__(self)
    #================================================
    def runServer(self):
        lAddress = ""
        lPort = 9010
        lBacklog = 10
        
        lSocket = socket.socket()
        lSocket.bind((lAddress, lPort))
        lSocket.listen(lBacklog)
        
        printf("Démarrage du serveur...\n")
        
        while True:
            lClient, lAddressC = lSocket.accept()    
            lData = lClient.recv(self.BUFFER_SIZE).decode()
            lData = sprintf("[server] : %s", lData)
            lClient.send(lData.encode())
            lClient.close()
        lSocket.close()
#================================================
    def callServer(self, _data):
        lAddress = "127.0.0.1"
        lPort = 9010
        
        lSocket = socket.socket()        
        lSocket.connect((lAddress, lPort))
        lSocket.send(_data.encode())
        lData = lSocket.recv(self.BUFFER_SIZE).decode()
        lSocket.close()
        return lData
#================================================
