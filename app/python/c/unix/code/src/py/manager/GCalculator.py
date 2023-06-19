#================================================
from functions import *
from manager.GObject import GObject
from manager.GCode import GCode
#================================================
class GCalculator(GObject):
    #================================================
    def __init__(self):
        GObject.__init__(self)
        self.m_expression = ""
        self.m_result = ""
    #================================================
    def clone(self):
        return GCalculator()
    #================================================
    def setObj(self, _obj):
        self.m_expression = _obj.m_expression
        self.m_result = _obj.m_result
    #================================================
    def serialize(self, _code = "calculator"):
        lDom = GCode()
        lDom.createDoc()
        lDom.addDatas(_code, "expression", self.m_expression)
        lDom.addDatas(_code, "result", self.m_result)
        lDom.addMap(_code, self.m_map)
        return lDom.toString()
    #================================================
    def deserialize(self, _data, _code = "calculator"):
        lDom = GCode()
        lDom.loadXml(_data)
        self.m_expression = lDom.getDatas(_code, "expression")
        self.m_result = lDom.getDatas(_code, "result")
        lDom.getMap(_code, self)
    #================================================
    def runCalculator(self):
        lData = self.serialize()
        lData = rdvcpy.callFacade("calculator", "run_calculator", lData).decode("utf-8") 
        self.deserialize(lData)
        self.m_logs.deserialize(lData)
#================================================
