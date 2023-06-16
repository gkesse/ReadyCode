#================================================
from functions import *
from manager.GObject import GObject
#================================================
class GSocket(GObject):
    #================================================
    BUFFER_SIZE = 10
    FIONREAD = 1074030207
    #================================================
    def __init__(self):
        GObject.__init__(self)
        self.m_socket = None
    #================================================
    def sendData(self, _data):
        self.m_socket.send(_data.encode())
    #================================================
    def readData(self):
        lData = ""
        while True:
            lBuffer = self.m_socket.recv(self.BUFFER_SIZE).decode()
            if not lBuffer: break
            lData += lBuffer
            lSockSize = array.array('i', [0])
            fcntl.ioctl(self.m_socket, self.FIONREAD, lSockSize)
            lBytes = lSockSize[0]
            printf("%d..\n", lBytes)
            if lBytes == 0: break
        return lData
    #================================================
    def closeSocket(self):
        self.m_socket.close()
    #================================================
    def runServer(self):
        lAddress = ""
        lPort = 9010
        lBacklog = 10
        
        lSocket = socket.socket()
        lSocket.bind((lAddress, lPort))
        lSocket.listen(lBacklog)
        
        printf("Démarrage du serveur...\n")
        lClient = GSocket()

        while True:
            lClient.m_socket, lAddressC = lSocket.accept()    
            lData = lClient.readData()
            lClient.sendData(lData)
        lSocket.close()
#================================================
    def callServer(self, _data):
        lAddress = "127.0.0.1"
        lPort = 9010
        
        lSocket = GSocket()
        lSocket.m_socket = socket.socket()        
        lSocket.m_socket.connect((lAddress, lPort))
        lSocket.sendData(_data)
        lData = lSocket.readData()
        lSocket.closeSocket()
        return lData
#================================================
