#================================================
# compile
#================================================
GSRC = ..\code\src
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
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\* $(GTARGET)
#================================================
# module
#================================================
GLIBS = $(GSRC)\libs
GLIBS_BIN = $(GLIBS)\bin
GLIBS_LIB = $(GLIBS)\lib
GLIBS_INC = $(GLIBS)\include
GLIBS_TMP = $(GLIBS)\tmp
GWGET = $(GLIBS_BIN)\wget.exe
#================================================
GLIBS_MOD =\
    $(GLIBS_LIB)/libbase64.a \
#================================================
module_im: $(GLIBS_MOD)
#================================================
$(GLIBS_LIB)/libbase64.a: 
	@if not exist $(GLIBS_BIN) ( mkdir $(GLIBS_BIN) )
	@if not exist $(GLIBS_LIB) ( mkdir $(GLIBS_LIB) )
	@if not exist $(GLIBS_INC) ( mkdir $(GLIBS_INC) )
	@if not exist $(GLIBS_TMP) ( mkdir $(GLIBS_TMP) )
	@cd $(GLIBS_TMP) && if not exist base64.h ( wget https://raw.githubusercontent.com/ReneNyffenegger/cpp-base64/master/base64.cpp )
	@cd $(GLIBS_TMP) && if not exist base64.h ( wget https://raw.githubusercontent.com/ReneNyffenegger/cpp-base64/master/base64.h )
	@cd $(GLIBS_TMP) && g++ -c base64.cpp -o base64.o
	@cd $(GLIBS_TMP) && ar rvs libbase64.a base64.o
	@echo f | xcopy /f /y $(GLIBS_TMP)\libbase64.a $(GLIBS_LIB)\libbase64.a
	@echo f | xcopy /f /y $(GLIBS_TMP)\base64.h $(GLIBS_INC)\base64\base64.h
	@del /q /s $(GLIBS_TMP)
#================================================
