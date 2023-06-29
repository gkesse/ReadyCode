#================================================
# compile
#================================================
GSRC = ..\code\src
GBIN = bin
GBUILD = build
GTARGET = bin\rdv_cpp.exe
GLIBS = $(GSRC)\libs
#================================================
GCLASSPATH := .
GCLASSPATH := $(GCLASSPATH);$(GBUILD)
GCLASSPATH := $(GCLASSPATH);$(GLIBS)\jdom-2.0.6.1.jar
GCLASSPATH := $(GCLASSPATH);$(GLIBS)\jaxen-1.1.1.jar
GCLASSPATH := $(GCLASSPATH);$(GLIBS)\MathParser.org-mXparser.jar
#================================================
all: clean compile run
all_g: clean compile_g run_g
#================================================
compile:
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@javac $(GSRC)\GMain.java -d $(GBUILD) -sourcepath $(GSRC) -classpath $(GCLASSPATH)
compile_g:
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@javac -g $(GSRC)\GMain.java -d $(GBUILD) -sourcepath $(GSRC) -classpath $(GCLASSPATH)
run:
	@java -classpath $(GCLASSPATH) GMain $(argv)
run_g:
	@jdb -classpath $(GCLASSPATH) -sourcepath $(GSRC) GMain $(argv)
clean:
	@del /q /s $(GBUILD)\*
#================================================
