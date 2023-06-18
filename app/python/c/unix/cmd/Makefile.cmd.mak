#================================================
# compile
#================================================
SHELL := /bin/bash
#================================================
GSRC = ../code/src
GRLIB_BIN = ../code/src
#================================================
# module
#================================================
module_c:
	@cd $(GSRC) && python3 setup.py build
module_i:
	@cd $(GSRC) && sudo python3 setup.py install
module_lsm:
	@ls -l  /usr/local/lib/python3.10/dist-packages/
module_lsp:
	@pip3 list
module_r:
	@cd $(GSRC) && python3 main.py
#================================================
# libs
#================================================
libs_i:
	@sudo apt install python3-distutils -y
	@sudo apt install python3-setuptools -y
	@sudo apt install python3-pip -y
libs_ls:
	@pip3 list
libs_ui:
	@sudo pip3 uninstall callFacade -y
	@sudo pip3 uninstall rdvcpy -y
#================================================
# infos
#================================================
infos:
	python3 --version
	python3 -m site --user-site
#================================================
