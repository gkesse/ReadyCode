#================================================
# compile
#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdv_cpp.exe
#================================================
all: clean_exe qmake compile run
all_r: run
all_g: run_g
#================================================
qmake:
	@qmake 
compile:
	@mingw32-make
run:
	@$(GTARGET) $(argv)
run_g:
	@gdb --args $(GTARGET) $(argv)
clean_exe: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GTARGET)
clean: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\* $(GTARGET)
#================================================
