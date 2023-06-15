#================================================
import sys
from lxml import etree as ET
from bs4 import BeautifulSoup
from html import escape
from xml.dom.minidom import parseString as string_to_dom
#================================================
def printf(format, *args):
    sys.stdout.write(format % args)
#================================================
