//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
//===============================================
class GManager {
private:
    GManager();
    
public:
    ~GManager();
    static GManager* Instance();
    sGManager* getData();
    
private:
    static GManager* m_instance;
    sGManager* mgr;
};
//==============================================
struct _sGManager {
	sGApp* app;
};
//==============================================
struct _sGApp {
	// app
	std::string app_name;
	// opencv
	std::string opencv_image_file;
	std::string opencv_video_file;
	std::string opencv_video_write;
	int opencv_camera_index;
};
//==============================================
#endif
//==============================================
