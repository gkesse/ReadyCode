#================================================
from functions import *
from manager.GManager import GManager
from manager.GCode import GCode
#================================================
class GCalculator(GManager):
    #================================================
    def __init__(self):
        GManager.__init__(self)
        self.m_expression = ""
        self.m_result = ""
    #================================================
    def serialize(self, _code = "calculator"):
        lDom = GCode()
        lDom.createDoc()
        lDom.addDatas(_code, "expression", utf8_to_b64(self.m_expression))
        lDom.addDatas(_code, "result", self.m_result)
        return lDom.toString()
    #================================================
    def deserialize(self, _data, _code = "calculator"):
        super().deserialize(_data)
        lDom = GCode()
        lDom.loadXml(_data)
        self.m_expression = b64_to_utf8(lDom.getDatas(_code, "expression"))
        self.m_result = lDom.getDatas(_code, "result")
    #================================================
    def run(self, _data):
        self.deserialize(_data)
        if self.m_method == "":
            self.m_logs.addError("La méthode est obligatoire.")
        elif self.m_method == "run_calculator":
            self.onRunCalculator(_data)
        else:
            self.m_logs.addError("La méthode est inconnue.")
    #================================================
    def onRunCalculator(self, _data):
        self.m_result = "12345"
        self.m_logs.addData(self.serialize())
#================================================
