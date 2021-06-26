#================================================
GSRC = ../code
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\rdcpp.exe

GINCS =\

GLIBS =\

GOBJS = \
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
#================================================
# cpp
all: compile run

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(argv)
clean: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q $(GBUILD)\*.o $(GTARGET)
#================================================
# git
gitc_init:
	@cd $(GGIT_PROJECT) && git init
gitc_status:
	@cd $(GGIT_PROJECT) && git status -u
gitc_add:
	@cd $(GGIT_PROJECT) && git add --all
gitc_commit_master:
	@cd $(GGIT_PROJECT) && git commit -m "Developpement standard avec un fichier unique"
gitc_commit_modular:
	@cd $(GGIT_PROJECT) && git commit -m "Developpement modulaire avec plusieurs fichiers"
gitc_branch_create:
	@cd $(GGIT_PROJECT) && git branch modular
gitc_branch_select:
	@cd $(GGIT_PROJECT) && git checkout modular
gitc_branch_select_2:
	@cd $(GGIT_PROJECT) && git switch modular
gitc_branch_create_select:
	@cd $(GGIT_PROJECT) && git checkout -b modular
gitc_branch_create_select_2:
	@cd $(GGIT_PROJECT) && git switch -c modular
gitc_branch_merge:
	@cd $(GGIT_PROJECT) && git checkout master
	@cd $(GGIT_PROJECT) && git merge modular
gitc_branch_list:
	@cd $(GGIT_PROJECT) && git branch
gitc_branch_delete:
	@cd $(GGIT_PROJECT) && git branch -d modular
gitc_branch_undo:
	@cd $(GGIT_PROJECT) && git switch -
gitc_branch_log:
	@cd $(GGIT_PROJECT) && git log modular
gitc_log:
	@cd $(GGIT_PROJECT) && git log
gitc_master_check:
	@cd $(GGIT_PROJECT) && git checkout master
	@cd $(GGIT_PROJECT) && git status
#================================================
# git
git_status:
	@cd $(GPROJECT_PATH) && git status -u
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
