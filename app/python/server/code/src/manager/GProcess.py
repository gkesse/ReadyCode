#================================================
from functions import *
from manager.GTest import GTest
#================================================
class GProcess:
    #================================================
    def __init__(self):
        pass
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
    #================================================
    def runServer(self):
        printf("runServer...\n")
#================================================
