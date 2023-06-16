#================================================
from functions import *
from manager.GManager import GManager
#================================================
class GServer(GManager):
    #================================================
    def __init__(self):
        GManager.__init__(self)
    #================================================
    def run(self, _data):
        self.deserialize(_data)
        if self.m_module == "":
            self.m_logs.addError("Le module est obligatoire.")
        elif self.m_module == "logs":
            self.m_logs.addLog("Le module a été trouvé.")
        else:
            self.m_logs.addError("Le module est inconnu.")
    #================================================
    def sendResponse(self, _data, _client):
        self.m_resp.loadData(self.m_logs.serialize())
        _client.sendData(self.m_resp.toString())
#================================================
