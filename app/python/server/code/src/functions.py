#================================================
import sys
import re
from lxml import etree as ET
from bs4 import BeautifulSoup
from html import escape
from html.parser import HTMLParser
from xml.dom.minidom import parseString as string_to_dom
#================================================
def printf(format, *args):
    sys.stdout.write(format % args)
#================================================
