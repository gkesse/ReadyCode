#================================================
from functions import *
from manager.GObject import GObject
from manager.GCode import GCode
#================================================
class GSocket(GObject):
    #================================================
    BUFFER_SIZE = 1024
    #================================================
    def __init__(self):
        GObject.__init__(self)
        self.m_socket = None
        self.m_address = ""
    #================================================
    def sendData(self, _data):
        self.m_socket.send(_data.encode())
    #================================================
    def readData(self):
        lData = self.m_socket.recv(self.BUFFER_SIZE).decode()
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
            lClient.m_socket, lClient.m_address = lSocket.accept()    
            lThread = threading.Thread(target=self.onThread, args=(lClient,))
            lThread.start()
        lSocket.close()
    #================================================
    @staticmethod
    def onThread(_params):
        lClient = _params
        lData = lClient.readData()
        lClient.sendData(lData)
        lClient.closeSocket()
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
    def callFacade(self, _module, _method, _data = ""):
        lDom = GCode()
        lDom.createDoc()
        lDom.addDatas("manager", "module", _module)
        lDom.addDatas("manager", "method", _method)
        lDom.loadData(_data)
        lData = lDom.toString()
        lData = self.callServer(lData)
        return lData
#================================================
