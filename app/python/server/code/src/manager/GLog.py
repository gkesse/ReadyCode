#================================================
from functions import *
#================================================
class GLog:
    #================================================
    def __init__(self):
        self.m_type = ""
        self.m_side = ""
        self.m_msg = ""
        self.m_map = []
    #================================================
    def setObj(self, _obj):
        self.m_type = _obj.m_type
        self.m_side = _obj.m_side
        self.m_msg = _obj.m_msg
    #================================================
    def addError(self, _msg):
        lObj = GLog()
        lObj.m_type = "error"
        lObj.m_side = "server_py"
        lObj.m_msg = _msg
        self.m_map.append(lObj)
    #================================================
    def addLog(self, _msg):
        lObj = GLog()
        lObj.m_type = "log"
        lObj.m_side = "server_py"
        lObj.m_msg = _msg
        self.m_map.append(lObj)
    #================================================
    def addData(self, _msg):
        lObj = GLog()
        lObj.m_type = "data"
        lObj.m_side = "server_py"
        lObj.m_msg = _msg
        self.m_map.append(lObj)
    #================================================
    def loadToMap(self, i):
        if i >= 1 and i <= len(self.m_map):
            lObj = self.m_map[i]
            lObj.setObj(self)
    #================================================
    def loadFromMap(self, i):
        if i >= 1 and i <= len(self.m_map):
            lObj = self.m_map[i]
            self.setObj(lObj)
    #================================================
    def print(self):
        for i in range(len(self.m_map)):
            lObj = self.m_map[i]
            printf("[%-5s] : %s\n", lObj.m_type, lObj.m_msg)
#================================================
