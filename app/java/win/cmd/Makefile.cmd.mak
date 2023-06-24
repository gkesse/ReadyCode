#================================================
# compile
#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdv_cpp.exe
#================================================
all: clean compile run
all_g: clean compile run_g
#================================================
compile:
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@javac -g $(GSRC)\GMain.java -d $(GBUILD) -sourcepath $(GSRC)
run:
	@java -classpath $(GBUILD) GMain $(argv)
run_g:
	@jdb -classpath $(GBUILD) GMain $(argv)
clean:
	@del /q /s $(GBUILD)\*
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
