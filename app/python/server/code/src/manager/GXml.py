#================================================
from functions import *
#================================================
class GXml:
    #================================================
    def __init__(self):
        self.m_node = None
    #================================================
    def createDoc(self):
        del self.m_node
        ET.XMLParser(remove_blank_text=True)
        self.m_node = ET.Element("rdv")
    #================================================
    def loadXml(self, _data):
        del self.m_node
        ET.XMLParser(remove_blank_text=True)
        lData = bytes(bytearray(_data, encoding='utf-8'))
        self.m_node = ET.fromstring(lData)
    #================================================
    def loadNode(self, _data):
        if _data == "":
            return
        lData = bytes(bytearray(_data, encoding='utf-8'))
        lNodes = ET.fromstring(lData)
        for lNode in lNodes:
            self.m_node.append(lNode)
    #================================================
    def createNode(self, _path, _value = ""):
        lPaths = _path.split("/")
        lPath = ""
        if _path[0] == "/":
            lPath = "/"
        j = 0
        lDom = GXml()
        lDom.m_node = self.m_node
        for i in range(len(lPaths)):
            lPathI = lPaths[i]
            if lPathI == "":
                continue
            if j != 0:
                lPath += "/"
            j += 1
            lPath += lPathI

            if not self.existNode(lPath):
                lDom.m_node = lDom.addObj(lPathI)
            else:
                lDom.m_node = self.getNode(lPath)
        if _value != "":
            lDom.setValue(_value)
        return lDom.m_node
    #================================================
    def countNode(self, _path):
        lNodes = self.m_node.xpath(_path)
        return len(lNodes)
    #================================================
    def existNode(self, _path):
        return (self.countNode(_path) != 0)
    #================================================
    def getNode(self, _path):
        lNodes = self.m_node.xpath(_path)
        if len(lNodes) == 0:
            return None
        return lNodes[0]
    #================================================
    def setValue(self, _value):
        if self.m_node == None:
            return
        self.m_node.text = _value
    #================================================
    def getValue(self):
        if self.m_node == None:
            return ""
        return self.m_node.text
    #================================================
    def addObj(self, _name):
        lNode = ET.SubElement(self.m_node, _name)
        return lNode
    #================================================
    def addData(self, _name, _value):
        lNode = ET.SubElement(self.m_node, _name)
        lNode.text = _value
    #================================================
    def toString(self):
        lData = ET.tostring(self.m_node)
        lData = BeautifulSoup(lData, "xml")
        lDom = string_to_dom(str(lData))
        lData = lDom.toprettyxml(indent="  ", encoding="utf-8").decode("utf-8")
        lDatas = list(filter(lambda x: len(x.strip()), lData.split('\n')))
        lData = '\n'.join(lDatas)
        return lData
    #================================================
    def toNode(self):
        lData = ET.tostring(self.m_node)
        lData = BeautifulSoup(lData, "xml")
        lDom = string_to_dom(str(lData))
        lData = lDom.toprettyxml(indent="  ")
        lDatas = list(filter(lambda x: len(x.strip()), lData.split('\n')))
        lData = '\n'.join(lDatas)
        lData = lData[lData.find("?>")+2:]
        return lData
    #================================================
    def print(self):
        printf("%s\n", self.toString())
#================================================
