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
    def createNode(self, _path):
        lPaths = _path.split("/")
        lPath = ""
        if _path[0] == "/":
            lPath = "/"
        j = 0
        for i in range(len(lPaths)):
            lPathI = lPaths[i]
            if lPathI == "":
                continue
            if j != 0:
                lPath += "/"
            j += 1
            lPath += lPathI
            printf("%s...\n", lPath)
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
    def print(self):
        printf("%s\n", self.toString())
#================================================
