#================================================
from functions import *
from manager.GObject import GObject
from manager.GTest import GTest
#================================================
class GProcess(GObject):
    #================================================
    def __init__(self):
        GObject.__init__(self)
    #================================================
    def init(self):
        pass
    #================================================
    def clean(self):
        pass
    #================================================
    def run(self):
        lModule = ""
        if len(sys.argv) > 1:
            lModule = sys.argv[1]
            
        if lModule == "":
            self.m_logs.addError("Le module est obligatoire.");
        elif lModule == "test":
            self.runTest();
        else:
            self.m_logs.addError("Le module est inconnu.");
    #================================================
    def runTest(self):
        lObj = GTest()
        lObj.run()
        self.m_logs.addLogs(lObj.m_logs)
#================================================