#================================================
from functions import *
from manager.GObject import GObject
from manager.GCalculator import GCalculator
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
        elif lMethod == "facade":
            self.runFacade()
        else:
            self.m_logs.addError("La méthode est inconnue.");
    #================================================
    def runFacade(self):
        lCalculator = GCalculator()
        lCalculator.m_expression = "10/2"
        lCalculator.runCalculator()
        self.m_logs.addLogs(lCalculator.m_logs)
#================================================
