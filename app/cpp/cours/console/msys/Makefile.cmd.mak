#================================================
GSRC = ../code/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/rdcpp

GGLAD_SRC = C:\Users\Admin\Downloads\RLib\glad\src

GINCS =\
    -IC:\Users\Admin\Downloads\RLib\include \

GLIBS =\
    -lglfw3 -lglew32 -lglu32 -lopengl32 -lm \
    
GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GGLAD_SRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GGLAD_SRC)/*.c)) \

GCFLAGS = \
    -g \
    -std=gnu11 \
    -DUSEGLEW \
    
GCPPFLAGS = \
    -g \
    -std=gnu++11 \
    -DUSEGLEW \
#================================================
# cpp
all: clean_exe compile run

compile: $(GOBJS)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	g++ $(GCPPFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCPPFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GGLAD_SRC)/%.c
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(argv)
run_g:
	@gdb --args $(GTARGET) $(argv)
clean_exe: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@rm -f $(GBIN)/*
clean: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	@rm -f $(GBUILD)/* $(GBIN)/*
#================================================    
# cmd
cmd_update:
	@echo pacman -Syu
cmd_run:
	@cd $(GPROJECT_PATH) && $(argv)
#================================================    
# git
git_install:
	@echo pacman -S --needed --noconfirm git
	@echo pacman -S --needed --noconfirm vim
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
git_pull:
	@cd $(GPROJECT_PATH) && git pull
git_push_u:
	@cd $(GPROJECT_PATH) && git push
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
