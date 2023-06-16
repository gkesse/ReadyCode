#================================================
from functions import *
from manager.GObject import GObject
from manager.GLog import GLog
from manager.GXml import GXml
from manager.GCode import GCode
from manager.GString import GString
from manager.GSocket import GSocket
#================================================
class GTest(GObject):
    #================================================
    def __init__(self):
        GObject.__init__(self)
    #================================================
    def run(self):
        lMethod = ""
        
        if len(sys.argv) > 2:
            lMethod = sys.argv[2]
            
        if lMethod == "":
            self.m_logs.addError("La méthode est obligatoire.");
        if lMethod == "string":
            self.runString()
        elif lMethod == "log":
            self.runLog()
        elif lMethod == "xml":
            self.runXml()
        elif lMethod == "code":
            self.runCode()
        elif lMethod == "socket_client":
            self.runSocketClient()
        elif lMethod == "facade":
            self.runFacade()
        else:
            self.m_logs.addError("La méthode est inconnue.");
    #================================================
    def runString(self):
        lString = GString()
        
        # m_data - print
        lString.m_data = "Bonjour tout le monde."
        lString.print()
        
        # sprintf
        lString.m_data = sprintf("Bonjour %s : v%f", "Python", 3.11)
        lString.print()        
    #================================================
    def runLog(self):
        lLog = GLog()
        lLog2 = GLog()
        lString = GString()
        
        # addError - addLog - addData - loadFromMap - print
        lLog.addError("La connexion au serveur a échoué.")
        lLog.addLog("Le module de supervision est chargé.")
        lLog.addData("La résolution de l'écran est 1200x976.")
        lLog.loadFromMap(1)
        lLog.print()
        
        # serialize
        lString.m_data = lLog.serialize()
        lString.print()
        lLog2.deserialize(lString.m_data)
        lString.m_data = lLog2.serialize()
        lString.print()
        self.m_logs.addLogs(lLog2)
    #================================================
    def runXml(self):
        lDom = GXml()
        lDomC1 = GXml()
        lDomC2 = GXml()
        
        # createDoc - addObj - addData - print
        lDom.createDoc()
        lDomC1.m_node = lDom.addObj("datas")
        lDomC2.m_node = lDomC1.addObj("data")
        lDomC2.addData("code", "logs")
        lDomC2.addData("type", "error")
        lDomC2.addData("side", "server_py")
        lDomC2.addData("msg", "La connexion au serveur a échoué.")
        lDom.print()
        
        # createNode
        lDom.createDoc()
        lDom.createNode("/rdv/datas/data/code", "log")
        lDom.createNode("/rdv/datas/data/code", "logs")
        lDom.print()
    #================================================
    def runCode(self):
        lDom = GCode()
        lDomC1 = GCode()
        lDomC2 = GCode()
        
        # createDoc - createDatas - createCode - print
        lDom.createDoc()
        lDom.createDatas()
        lDom.createDatas()
        lDom.createCode("logs")
        lDom.createCode("logs")
        lDom.addDatas("logs", "type", "error")
        lDom.addDatas("logs", "side", "server_py")
        lDom.addDatas("logs", "msg", "La connexion au serveur a échoué.")
        lDom.print()
    #================================================
    def runSocketClient(self):
        lClient = GSocket()
        lData = lClient.callServer("Bonjour tout le monde.");
        printf("%s\n", lData)
    #================================================
    def runFacade(self):
        # data
        lLog = GLog()
        lLog.addError("La connexion au serveur a échoué.")
        lLog.addLog("Le module de supervision est chargé.")
        lLog.addData("La résolution de l'écran est 1200x976.")
        lLog.loadFromMap(1)
        
        # facade
        lClient = GSocket()
        lData = lLog.serialize()
        lData = lClient.callFacade("logs", "save_logs", lData);
        printf("%s\n", lData)
#================================================
