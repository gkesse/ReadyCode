#================================================
from functions import *
from manager.GObject import GObject
from manager.GCode import GCode
#================================================
class GManager(GObject):
    #================================================
    def __init__(self):
        GObject.__init__(self)
        self.m_module = ""
        self.m_method = ""
        self.m_resp = GCode()
        self.m_resp.createDoc()
    #================================================
    def serialize(self, _code = "manager"):
        lDom = GCode()
        lDom.createDoc()
        lDom.addDatas(_code, "module", self.m_module)
        lDom.addDatas(_code, "method", self.m_method)
        return lDom.toString()
    #================================================
    def deserialize(self, _data, _code = "manager"):
        lDom = GCode()
        lDom.loadXml(_data)
        self.m_module = lDom.getDatas(_code, "module")
        self.m_method = lDom.getDatas(_code, "method")
#================================================
