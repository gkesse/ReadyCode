#================================================
# compile
#================================================
GSRC = ..\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdv_cpp.exe
#================================================
all: clean_exe qmake compile run
all_g: clean_exe qmake compile run_g
#================================================
qmake:
	@qmake 
compile:
	@mingw32-make
run:
	@$(GTARGET) $(argv)
run_g:
	@envs.bat && gdb -ex run --args $(GTARGET) $(argv)
clean_exe: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GTARGET)
clean: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GBUILD)\* $(GTARGET)
#================================================
