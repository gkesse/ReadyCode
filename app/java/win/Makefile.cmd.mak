#================================================
# compile
#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdv_cpp.exe
#================================================
all: run
#================================================
run:
	@cd $(GPROJECT_SRC) && .\main.bat $(argv)
#================================================
# java
java_version:
	@java -version
#================================================
# git
git_status:
	@cd $(GPROJECT_PATH) && git status -u
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
