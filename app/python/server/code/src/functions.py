#================================================
import sys
import io
import socket
import win32api
import threading
import base64
#================================================
from lxml import etree as ET
from bs4 import BeautifulSoup
from html import escape
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
def utf8_to_b64(_data):
    lData = _data.encode('utf8')
    lData = base64.b64encode(lData)
    lData = lData.decode('utf8')
    return lData
#================================================
def b64_to_utf8(_data):
    lData = _data.encode('utf8')
    lData = base64.b64decode(lData)
    lData = lData.decode('utf8')
    return lData
#================================================
def handler(a, b=None):
    sys.exit(1)
#================================================
def install_handler():
    if sys.platform == "win32":
        win32api.SetConsoleCtrlHandler(handler, True)
#================================================
