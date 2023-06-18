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
            , ["rdvcpy_module.c", "GFunctions.c"]
        )
    ])
)
#================================================
