#================================================
# compile
#================================================
GPROJECT_SRC = ..\code\src
#================================================
all: run
all_g: run_g

run:
	@cd $(GPROJECT_SRC) && python main.py $(argv)
run_g:
	@cd $(GPROJECT_SRC) && python -m pdb -c continue main.py $(argv)
#================================================
# python
#================================================
py_version:
	@python --version
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
