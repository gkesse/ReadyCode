#================================================
import sys
import io
import rdvcpy
#================================================
from lxml import etree as ET
from bs4 import BeautifulSoup
from xml.dom.minidom import parseString as string_to_dom
#================================================
def printf(_format, *_args):
    sys.stdout.write(_format % _args)
#================================================
def sprintf(_format, *_args):
    lBuffer = io.StringIO()
    lBuffer.write(_format % _args)
    return lBuffer.getvalue()
#================================================
