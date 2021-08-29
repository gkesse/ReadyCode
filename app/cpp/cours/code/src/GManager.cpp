//===============================================
#include "GManager.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
	// manager
	mgr = new sGManager;
	// app
	mgr->app = new sGApp;
	mgr->app->app_name = "ReadyApp";
	mgr->app->opencv_image_file = "C:/Users/Admin/Downloads/Programs/ReadyData/img/gazebo_uav.png";
	mgr->app->opencv_video_file = "C:/Users/Admin/Downloads/Programs/ReadyData/video/cgi_animation.mp4";
}
//===============================================
GManager::~GManager() {

}
//===============================================
GManager* GManager::Instance() {
    if(m_instance == 0) {
        m_instance = new GManager;
    }
    return m_instance;
}
//===============================================
sGManager* GManager::getData() {
    return mgr;
}
//===============================================
