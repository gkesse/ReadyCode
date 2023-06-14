#================================================
from functions import *
from manager.GHtmlParser import GHtmlParser
#================================================
class GXml:
    #================================================
    def __init__(self):
        self.m_node = None
    #================================================
    def createDoc(self):
        ET.XMLParser(remove_blank_text=True)
        self.m_node = ET.Element("rdv")
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
