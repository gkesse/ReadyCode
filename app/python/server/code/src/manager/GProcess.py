#================================================
from functions import *
from manager.GObject import GObject
from manager.GTest import GTest
from manager.GSocket import GSocket
#================================================
class GProcess(GObject):
    #================================================
    def __init__(self):
        GObject.__init__(self)
    #================================================
    def run(self):
        lModule = ""
        if len(sys.argv) > 1:
            lModule = sys.argv[1]
            
        if lModule == "test":
            self.runTest();
        elif lModule == "server":
            self.runServer();
    #================================================
    def runTest(self):
        lObj = GTest()
        lObj.run()
        self.m_logs.addLogs(lObj.m_logs)
    #================================================
    def runServer(self):
        lObj = GSocket()
        lObj.runServer()
        self.m_logs.addLogs(lObj.m_logs)
#================================================
