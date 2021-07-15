#================================================
GSRC = ../code
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/rdc

GINCS = \
    
GLIBS = \
    -lpthread -lzmq \
    
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \

GCFLAGS = \
    -std=gnu11 \
    
#================================================
# c
all: clean_exe compile run

compile: $(GOBJS)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@gcc $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	@gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(argv)
clean_exe: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@rm -f $(GTARGET)
clean: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	@rm -f $(GBUILD)/*.o $(GTARGET)
#================================================    
# zeromq
zeromq_install:
	@sudo apt install -y libzmq3-dev
#================================================    
# git
git_install:
	@sudo apt install -y git
git_config:
	@git config --global user.name "Gerard KESSE"
	@git config --global user.email "tiakagerard@hotmail.com"
	@git config --global core.editor "vim"
	@git config --list
git_store:
	@git config credential.helper store
git_status:
	@cd $(GPROJECT_PATH) && git status -u
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
