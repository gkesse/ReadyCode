#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdcpp.exe

GGLAD_SRC = C:\Users\Admin\Downloads\RLib\glad\src

GINCS =\
    -IC:\Users\Admin\Downloads\Compressed\glfw-3.3.4.bin.WIN32\glfw-3.3.4.bin.WIN32\include \
    -IC:\Users\Admin\Downloads\RLib\glad\include \
    
GLIBS =\
    -LC:\Users\Admin\Downloads\Compressed\glfw-3.3.4.bin.WIN32\glfw-3.3.4.bin.WIN32\lib-mingw-w64 \
    -lglfw3 -lgdi32
    
GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GGLAD_SRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GGLAD_SRC)/*.c)) \

GCFLAGS =\
    -g \
    -std=gnu++11 \
#================================================
# cpp
all: clean_exe compile run
all_g: clean_exe compile run_g

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GGLAD_SRC)/%.c
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
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
