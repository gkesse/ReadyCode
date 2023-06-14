#================================================
# compile
#================================================
GPROJECT_SRC = ..\code\src
GLIBS_BIN = ..\code\src\libs\bin
#================================================
all: run
all_g: run_g

run:
	@cd $(GPROJECT_SRC) && python main.py $(argv)
run_g:
	@cd $(GPROJECT_SRC) && python -m pdb -c continue main.py $(argv)
#================================================
# libs
#================================================
libs:
	@pip install bs4
	@pip list
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
# git
#================================================
git_status:
	@cd $(GPROJECT_PATH) && git status -u
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
