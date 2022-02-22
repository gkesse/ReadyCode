#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\rdc.exe

GRLIB = C:\Users\Admin\Downloads\Programs\ReadyLib\dev\mingw

GINCS = \
    -I$(GSRC)\manager \
    -I$(GRLIB)\include \
    -I$(GRLIB)\include\libxml2 \
    -I$(GRLIB)\src\xml \
    
GLIBS = \
    -L$(GRLIB)\lib \
	-lxml2 -lsqlite3 -lgsl \
	
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c)) \
    $(patsubst $(GRLIB)/src/xml/%.c, $(GBUILD)/%.o, $(wildcard $(GRLIB)/src/xml/*.c)) \

GCFLAGS = \
    -g \

#================================================
# c
all: clean_exe compile run
all_g: run_g

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	gcc $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GRLIB)/src/xml/%.c
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(argv)
run_g:
	@gdb --args $(GTARGET) $(argv)
clean_exe: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GBIN)\.exe
clean: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\*.o $(GBIN)\.exe
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
