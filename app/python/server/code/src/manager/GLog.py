#================================================
from functions import *
from manager.GCode import GCode
#================================================
class GLog:
    #================================================
    def __init__(self):
        self.m_type = ""
        self.m_side = ""
        self.m_msg = ""
        self.m_map = []
    #================================================
    def clone(self):
        return GLog()
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
    def addLogs(self, _obj):
        for i in range(len(_obj.m_map)):
            lObj = _obj.m_map[i]
            lNew = GLog()
            lNew.setObj(lObj)
            self.m_map.append(lNew)
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
    def serialize(self, _code = "logs"):
        lDom = GCode()
        lDom.createDoc()
        lDom.addDatas(_code, "type", self.m_type)
        lDom.addDatas(_code, "side", self.m_side)
        lDom.addDatas(_code, "msg", self.m_msg)
        lDom.addMap(_code, self.m_map)
        return lDom.toString()
    #================================================
    def deserialize(self, _data, _code = "logs"):
        lDom = GCode()
        lDom.loadXml(_data)
        self.m_type = lDom.getDatas(_code, "type")
        self.m_side = lDom.getDatas(_code, "side")
        self.m_msg = lDom.getDatas(_code, "msg")
        lDom.getMap(_code, self)
    #================================================
    def print(self):
        for i in range(len(self.m_map)):
            lObj = self.m_map[i]
            printf("[%-5s] : %s\n", lObj.m_type, lObj.m_msg)
#================================================
