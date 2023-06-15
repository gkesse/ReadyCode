#================================================
from functions import *
from manager.GXml import GXml
#================================================
class GCode(GXml):
    #================================================
    def __init__(self):
        GXml.__init__(self)
    #================================================
    def createDatas(self):
        lDom = GCode()
        lDom.m_node = self.getNode(sprintf("/rdv/datas"))
        if lDom.m_node == None:
            lDom.m_node = self.createNode("/rdv/datas")
        return lDom.m_node
    #================================================
    def createCode(self, _code):
        lDom = GCode()
        lDom.m_node = self.getNode(sprintf("/rdv/datas/data[code='%s']", _code))
        if lDom.m_node == None:
            lDom.m_node = self.createDatas()
            lDom.m_node = lDom.addObj("data")
            lDom.addData("code", _code)
        return lDom.m_node
    #================================================
    def addDatas(self, _code, _name, _value):
        if _value == "":
            return
        lDom = GCode()
        lDom.m_node = self.getNode(sprintf("/rdv/datas/data[code='%s']/%s", _code, _name))
        if lDom.m_node == None:
            lDom.m_node = self.createCode(_code)
            lDom.addData(_name, _value)
        else:
            lDom.setValue(_value)
        return lDom.m_node
    #================================================
    def addMap(self, _code, _map):
        lSize = len(_map)
        if lSize == 0:
            return
            
        lDom = GCode()
        lDom.m_node = self.getNode(sprintf("/rdv/datas/data[code='%s']/map", _code))

        if lDom.m_node == None:
            lDom.m_node = self.createCode(_code)
            lDom.m_node = lDom.addObj("map")

        for i in range(lSize):
            lObj = _map[i]
            lData = lObj.serialize(_code)
            lData = self.toDatas(lData)
            lDom.loadNode(lData)
    #================================================
    def getDatas(self, _code, _name):
        lDom = GCode()
        lDom.m_node = self.getNode(sprintf("/rdv/datas/data[code='%s']/%s", _code, _name))
        lData = ""
        if lDom.m_node != None:
            lData = lDom.getValue()
        return lData
    #================================================
    def getMap(self, _code, _obj):
        _obj.m_map = []
        lCount = self.countNode(sprintf("/rdv/datas/data[code='%s']/map/data", _code))
        if lCount == 0: return
        lDom = GCode()
        for i in range(lCount):
            lDom.m_node = self.getNode(sprintf("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code, i + 1))
            lData = lDom.toNode()
            lData = lDom.toCode(lData)
            lObj = _obj.clone()
            lObj.deserialize(lData, _code)
            lData = lObj.serialize(_code)
            _obj.m_map.append(lObj)
    #================================================
    def toDatas(self, _data):
        if _data == "":
            return ""
        lDom = GCode()
        lDomC = GCode()
        lDom.loadXml(_data)
        lDomC.m_node = lDom.getNode(sprintf("/rdv/datas"))
        return lDomC.toNode()
    #================================================
    def toCode(self, _data):
        if _data == "":
            return ""
        lDom = GCode()
        lDomC = GCode()
        lDom.createDoc()
        lDomC.m_node = lDom.createDatas()
        lData = sprintf("<rdv>%s</rdv>", _data)
        lDomC.loadNode(lData)
        return lDom.toString()
#================================================
