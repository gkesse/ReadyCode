#================================================
GSRC = ../code/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\rdv_cpp.exe
#================================================
GINCS =\
    -I$(GSRC)/manager \
    -I$(GSRC)/libs/include \
    -I$(GSRC)/libs/include/libxml2 \
	    
GLIBS =\
    -L$(GSRC)/libs/lib \
    -lws2_32 -lxml2 -ljson-c -lb64c -liconv -ltinyexpr \
	    
GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GSRC)/manager/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.cpp)) \

GCFLAGS =\
    -g \
    -std=gnu++11 \
#================================================
# cpp
#================================================
all: clean_exe compile run
all_g: clean_exe compile run_g
all_s: clean_exe compile copy_s run_s
all_sg: clean_exe compile copy_s run_sg

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
	@envs.bat && $(GTARGET) $(argv)
run_g:
	@envs.bat && gdb -ex run --args $(GTARGET) $(argv)
run_s:
	@envs.bat && $(GBIN)\rdvc_server.exe $(argv)
run_sg:
	@envs.bat && gdb -ex run --args $(GBIN)\rdvc_server.exe $(argv)
copy_s:
	@echo f | xcopy /f /y $(GTARGET) $(GBIN)\rdvc_server.exe
clean_exe: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GTARGET)
clean: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\*.o $(GTARGET)
#================================================
