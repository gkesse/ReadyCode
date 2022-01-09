//===============================================
#ifndef _GOpenCV_
#define _GOpenCV_
//===============================================
#include "GObject.h"
//===============================================
#define GOPENCV GOpenCV::Instance()
//===============================================
class GXml;
class GSocket;
//===============================================
class GOpenCV : public GObject {
public:
    GOpenCV(bool _init = false);
    ~GOpenCV();
    static GOpenCV* Instance();
    //
    void run(int _argc, char** _argv);
    //
    GOpenCV& createWindow(const std::string& _winname, int _flags);
    //
    int waitKey(int _ms);
    //
    GOpenCV& createImage(int _width, int _height, int _type, const cv::Scalar& _color);
    GOpenCV& createImageRgb(int _width, int _height, const cv::Scalar& _color);
    GOpenCV& showImage(GOpenCV& _img);
    //
    void createDoms();
    std::string getTitle() const;
    int getWidth() const;
    int getHeight() const;
    int getWaitKey() const;
    cv::Scalar getBgColor() const;
    int getTimer() const;
    //
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    void onModule(GObject* _request, GSocket* _client);
    //
    void onRunOpenCV(GObject* _request, GSocket* _client);
    static DWORD WINAPI onRunOpenCVThread(LPVOID _params);

private:
    static GOpenCV* m_instance;
    cv::Mat m_img;
    std::string m_winname;
    //
    GObject* m_request;
    GSocket* m_client;
};
//==============================================
#endif
//==============================================
