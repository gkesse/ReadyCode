#================================================
SHELL := /bin/bash
#================================================
GSRC = ../code/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/rdcpp.exe

GRLIB = ../../incs

GINCS =\
    -I$(GSRC)/manager \
	-I/usr/include/libxml2 \
	-I/usr/local/include \
    -I$(GRLIB)/include \
	
GLIBS =\
    -L/usr/local/lib \
    -lxml2 -lmysqlcppconn -lcurl -lssl -lcrypto -ljson-c \
    -lPocoFoundation -lPocoNet  -lPocoNetSSL -lPocoUtil -lPocoXML \
	
GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GSRC)/manager/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.cpp)) \
    $(patsubst $(GRLIB)/src/%.cpp, $(GBUILD)/%.o, $(wildcard $(GRLIB)/src/*.cpp)) \

GCFLAGS =\
    -g \
    -std=gnu++11 \
#================================================
# cpp
all: clean_exe compile run
all_g: clean_exe compile run_g

compile: $(GOBJS)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GRLIB)/src/%.cpp
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@source envs.sh && $(GTARGET) $(argv)
run_g:
	@source envs.sh && gdb -ex run --args $(GTARGET) $(argv)
clean_exe: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	rm -f $(GTARGET)
clean: 
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	rm -f $(GBUILD)/* $(GTARGET)
#================================================    
# git
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin main
git_push_u:
	@cd $(GPROJECT_PATH) && git push -u origin main
git_pull:
	@cd $(GPROJECT_PATH) && git pull
git_status:
	@cd $(GPROJECT_PATH) && git status -u
git_store:
	@git config credential.helper store
git_branch_2_1:
	@git checkout 2.1
git_cmd:
	@cd $(GPROJECT_PATH) && $(argv)
#================================================    
# server
server_install: 
	@cd $(GPROJECT_SCRIPTS) && ./000001-installer_serveur.sh
server_start:
	@cd $(GPROJECT_SCRIPTS) && ./000002-demarrer_serveur.sh
server_nohup:
	@cd $(GPROJECT_SCRIPTS) && nohup ./000002-demarrer_serveur.sh &
server_systemd: server_systemd_stop server_install
	@cd $(GPROJECT_SCRIPTS) && sudo ./000004-configurer_serveur_systemd.sh
server_systemd_start:
	@cd $(GPROJECT_SCRIPTS) && sudo systemctl restart pad
server_systemd_stop:
	@cd $(GPROJECT_SCRIPTS) && sudo systemctl stop pad
#================================================    
