#================================================
from functions import *
from manager.GLog import GLog
#================================================
class GObject:
    #================================================
    def __init__(self):
        self.m_logs = GLog()
        self.m_map = []
    #================================================
    def clone(self):
        return GObject()
    #================================================
    def setObj(self, _obj):
        pass
    #================================================
    def getLogs(self):
        return self.m_logs
    #================================================
    def loadToMap(self, i):
        if i >= 1 and i <= len(self.m_map):
            lObj = self.m_map[i - 1]
            lObj.setObj(self)
    #================================================
    def loadFromMap(self, i):
        if i >= 1 and i <= len(self.m_map):
            lObj = self.m_map[i - 1]
            self.setObj(lObj)
    #================================================
    def serialize(self, _code = "object"):
        return ""
    #================================================
    def deserialize(self, _data, _code = "object"):
        pass
    #================================================
    def print(self):
        printf("%s\n", self.serialize())
#================================================
