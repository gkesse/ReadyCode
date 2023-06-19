#================================================
from setuptools import setup, Extension
#================================================
setup(
    name='rdvcpy'
    , version='1.0'
    , description='Package Extension C pour Python par ReadyDev'
    , author="ReadyDev"
    , author_email="readydevz@gmail.com"
    , ext_modules=([
        Extension(
            "rdvcpy"
            , [ 
                "rdvcpy_module.c"
                , "c/manager/GFunctions.c"
                , "c/manager/GString.c"
                , "c/manager/GVector.c"
                , "c/manager/GXml.c"
                , "c/manager/GCode.c"
                , "c/manager/GLog.c"
                , "c/manager/GObject.c"
                , "c/manager/GServer.c"
              ]
            , include_dirs=["c/manager", "/usr/include/libxml2"]
            , libraries=["xml2"]
        )
    ])
)
#================================================
