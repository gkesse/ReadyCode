#================================================
from functions import *
from manager.GLog import GLog
from manager.GXml import GXml
#================================================
class GTest:
    #================================================
    def __init__(self):
        pass
    #================================================
    def run(self):
        lMethod = ""
        
        if len(sys.argv) > 2:
            lMethod = sys.argv[2]
            
        if lMethod == "log":
            self.runLog();
        if lMethod == "xml":
            self.runXml();
    #================================================
    def runLog(self):
        lLog = GLog()
        
        # addError - addLog - addData - loadFromMap - print
        lLog.addError("La connexion au serveur a échoué.")
        lLog.addLog("Le module de supervision est chargé.")
        lLog.addData("La résolution de l'écran est 1200x976.")
        lLog.loadFromMap(1);
        lLog.print()
    #================================================
    def runXml(self):
        lDom = GXml()
        lDomC1 = GXml()
        lDomC2 = GXml()
        
        # createDoc - addObj
        lDom.createDoc()
        lDomC1.m_node = lDom.addObj("datas")
        lDomC2.m_node = lDomC1.addObj("data")
        lDomC2.addData("code", "logs")
        lDomC2.addData("type", "error")
        lDomC2.addData("side", "server_py")
        lDomC2.addData("msg", "La connexion au serveur a échoué.")
        lDom.print()
#================================================
