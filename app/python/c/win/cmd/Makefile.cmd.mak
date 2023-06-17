#================================================
# compile
#================================================
GSRC = ..\code\src
GLIBS_BIN = ..\code\src\libs\bin
#================================================
all: run
all_g: run_g

run:
	@cd $(GSRC) && python main.py $(argv)
run_g:
	@cd $(GSRC) && python -m pdb -c continue main.py $(argv)
#================================================
# module
#================================================
module:
	@cd $(GSRC) && python setup.py build --compiler=mingw32
#================================================
# libs
#================================================
libs:
	@pip install setuptools==58.2.0
	@pip list
#================================================
infos:
	python --version
	python -m site --user-site
#================================================
# pip
#================================================
pip:
	@cd $(GLIBS_BIN) && curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py
	@cd $(GLIBS_BIN) && python get-pip.py
#================================================
# lxml
#================================================
lxml:
	@cd $(GLIBS_BIN) && pip install lxml-4.9.0-cp311-cp311-win_amd64.whl
#================================================
# python
#================================================
python:
	@python --version
	@python -m pip install --upgrade pip
#================================================
