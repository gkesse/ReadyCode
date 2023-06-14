#================================================
from functions import *
from manager.GLog import GLog
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
    #================================================
    def runLog(self):
        lLog = GLog()
        lLog.addError("La connexion au serveur a échoué.")
        lLog.addLog("Le module de supervision est chargé.")
        lLog.addData("La résolution de l'écran est 1200x976.")
        lLog.print()
#================================================
