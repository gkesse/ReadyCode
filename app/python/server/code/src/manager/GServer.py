#================================================
from functions import *
from manager.GManager import GManager
from manager.GCalculator import GCalculator
#================================================
class GServer(GManager):
    #================================================
    def __init__(self):
        GManager.__init__(self)
    #================================================
    def sendResponse(self, _data, _client):
        self.m_resp.loadData(self.m_logs.serialize())
        _client.sendData(self.m_resp.toString())
    #================================================
    def run(self, _data):
        self.deserialize(_data)
        if self.m_module == "":
            self.m_logs.addError("Le module est obligatoire.")
        elif self.m_module == "calculator":
            self.runCalculator(_data)
        else:
            self.m_logs.addError("Le module est inconnu.")
    #================================================
    def runCalculator(self, _data):
        lObj = GCalculator()
        lObj.run(_data)
        self.m_logs.addLogs(lObj.m_logs)
        self.m_resp.loadData(lObj.serialize())
#================================================
