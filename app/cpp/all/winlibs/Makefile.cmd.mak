#================================================
GSRC = ..\code
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\rdcpp.exe

GFTP_SRC = C:\Users\Admin\Downloads\RLib\ftp\fineftp-server\fineftp-server\src
GASIO_SRC = C:\Users\Admin\Downloads\RLib\boost\asio\asio\src

GINCS = \
    -IC:\Users\Admin\Downloads\RLib\csv\fast-cpp-csv-parser \
    -IC:\Users\Admin\Downloads\RLib\ftp\fineftp-server\fineftp-server\include \
    -IC:\Users\Admin\Downloads\RLib\ftp\fineftp-server\fineftp-server\src \
    -IC:\Users\Admin\Downloads\RLib\boost\asio\asio\include \
    
GLIBS = \

GOBJS = \
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GFTP_SRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GFTP_SRC)/*.cpp)) \

GCFLAGS = \
    -std=gnu++14 \
    -DASIO_HEADER_ONLY \
#================================================
# cpp
all: clean_exe compile run

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GFTP_SRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GASIO_SRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
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
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
