#================================================
GSRC = ..\code
GBIN = bin
GBUILD = build
GTARGET = bin\rdcpp.exe

GINCS = \
    -IC:\Users\Admin\Downloads\ocilib-4.7.3-windows\include \
    
GLIBS = \
    -LC:\Users\Admin\Downloads\ocilib-4.7.3-windows\lib64 \
    -lociliba -locilibw \
    
GOBJS = \
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \

GCFLAGS = \
    -std=gnu++11 \
    
#================================================
# cpp
all: clean_exe compile run

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(argv)
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
