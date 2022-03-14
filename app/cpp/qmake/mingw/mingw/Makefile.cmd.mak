#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdcpp.exe
#================================================
# cpp
all: clean_exe qmake compile run
all_g: clean_exe qmake compile run_g

qmake:
	@qmake 
compile:
	@mingw32-make
run:
	@$(GTARGET) $(argv)
run_g:
	@gdb --args $(GTARGET) $(argv)
clean_exe: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GBIN)\*
clean: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\* $(GBIN)\*
#================================================
# git
git_status:
	@cd $(GPROJECT_PATH) && git status -u
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_pull:
	@cd $(GPROJECT_PATH) && git pull
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
