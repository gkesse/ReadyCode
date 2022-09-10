#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdcpp.exe
GRLIB = ../../incs
#================================================
GRLIB = ${GPROJECT_ROOT}\ReadyLib\dev\mingw
#================================================
GINCS =\
    -I$(GSRC)/manager \
    -I$(GRLIB)/include \
	
GLIBS =\
    -L$(GRLIB)/lib \
    -lcurl \
    
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
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
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
