#================================================
from distutils.core import setup, Extension
#================================================
def main():
    setup(
        name="fputs"
        , version="1.0.0"
        , description="Module de gestion de connexion socket"
        , author="Gerard KESSE"
        , author_email="readydevz@gmail.com"
        , ext_modules=[Extension("fputs", ["fputsmodule.c"])]
    )
#================================================
if __name__ == "__main__":
    main()
#================================================
