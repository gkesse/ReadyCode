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
module_cm: module_clm
	@cd $(GSRC) && python3 setup.py build
module_im:
	@cd $(GSRC) && sudo python3 setup.py install
module_ip:
	@sudo apt install python3-setuptools -y
	@sudo apt install python3-pip -y
	@sudo apt install libxml2-dev -y
module_lsm:
	@ls -l  /usr/local/lib/python3.10/dist-packages/
module_lsp:
	@pip3 list
module_r:
	@cd $(GSRC)/py && python3 main.py
module_uim:
	@sudo pip3 uninstall rdvcpy -y
module_clm:
	@cd $(GSRC) && sudo rm -rf build
module_pyi:
	python3 --version
	python3 -m site --user-site
#================================================
