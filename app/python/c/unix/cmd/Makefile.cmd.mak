#================================================
# compile
#================================================
SHELL := /bin/bash
#================================================
GSRC = ../code/src
GSRC_C = $(GSRC)/c
GSRC_PY = $(GSRC)/py
GLIBS = $(GSRC_C)/libs
GLIBS_BIN = $(GLIBS)/bin
GLIBS_LIB = $(GLIBS)/lib
GLIBS_INC = $(GLIBS)/include
GLIBS_TMP = $(GLIBS)/tmp
#================================================
# module
#================================================
module_cm: module_clm
	@cd $(GSRC) && python3 setup.py build
module_im:
	@cd $(GSRC) && sudo python3 setup.py install
module_ip:
	@sudo apt install python3-pip -y
	@sudo apt install libxml2-dev -y
	@pip3 install setuptools
	@pip3 install lxml
	@pip3 install bs4
module_lsm:
	@ls -l  /usr/local/lib/python3.10/dist-packages/
module_lsp:
	@pip3 list
module_r:
	@cd $(GSRC_PY) && python3 main.py $(argv)
module_uim:
	@sudo pip3 uninstall rdvcpy -y
module_clm:
	@cd $(GSRC) && sudo rm -rf build
module_pyi:
	python3 --version
	python3 -m site --user-site
#================================================
module_bi: module_bi_tinyexpr
#================================================
module_bi_tinyexpr:
	@if ! [ -d $(GLIBS_TMP) ] ; then mkdir -p $(GLIBS_TMP) ; fi
	@if ! [ -d $(GLIBS_INC) ] ; then mkdir -p $(GLIBS_INC) ; fi
	@if ! [ -d $(GLIBS_LIB) ] ; then mkdir -p $(GLIBS_LIB) ; fi
	@if ! [ -d $(GLIBS_BIN) ] ; then mkdir -p $(GLIBS_BIN) ; fi
	@if ! [ -e $(GLIBS_TMP)/tinyexpr.c ] ; then cd $(GLIBS_TMP) && wget https://raw.githubusercontent.com/codeplea/tinyexpr/master/tinyexpr.c ; fi
	@if ! [ -e $(GLIBS_TMP)/tinyexpr.h ] ; then cd $(GLIBS_TMP) && wget https://raw.githubusercontent.com/codeplea/tinyexpr/master/tinyexpr.h ; fi
	@if ! [ -e $(GLIBS_TMP)/tinyexpr.o ] ; then cd $(GLIBS_TMP) && gcc -c tinyexpr.c -o tinyexpr.o -I. ; fi
	@if ! [ -e $(GLIBS_TMP)/libtinyexpr.a ] ; then cd $(GLIBS_TMP) && ar rcs libtinyexpr.a tinyexpr.o ; fi
	@if ! [ -e $(GLIBS_LIB)/libtinyexpr.a ] ; then cp $(GLIBS_TMP)/libtinyexpr.a $(GLIBS_LIB)/libtinyexpr.a ; fi
	@if ! [ -e $(GLIBS_INC)/tinyexpr.h ] ; then cp $(GLIBS_TMP)/tinyexpr.h $(GLIBS_INC)/tinyexpr.h ; fi
	@if [ -d $(GLIBS_TMP) ] ; then rm -rf $(GLIBS_TMP) ; fi
#================================================