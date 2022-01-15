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
    GOpenCV();
    ~GOpenCV();
    static GOpenCV* Instance();
    //
    void run(int _argc, char** _argv);
    //
    GOpenCV& createWindow(const std::string& _winname, int _flags);
    GOpenCV& closeWindow();
    //
    int waitKey(int _ms);
    //
    GOpenCV& createImage(int _width, int _height, int _type, const cv::Scalar& _color);
    GOpenCV& createImageRgb(int _width, int _height, const cv::Scalar& _color);
    GOpenCV& showImage(GOpenCV& _img);
    GOpenCV& loadImage(const std::string& _filename);
    //
    void createDoms();
    std::string getTitle() const;
    int getWidth() const;
    int getHeight() const;
    int getWaitKey() const;
    cv::Scalar getBgColor() const;
    int getTimer() const;
    //
    void createOpenCV();
    void addWindowId(int _id);
    void addWindowIName(const std::string& _winname);
    //
    void saveWindowId(int _id);
    void clearWindowId();
    void incWindowId();
    int getWindowId() const;
    //
    static void CALLBACK onTimer(HWND hwnd, UINT uMsg, UINT_PTR timerId, DWORD dwTime);
    //
    void onModule(GObject* _request, GSocket* _client);
    void addModule(int _id, GOpenCV* _opencv);
    GOpenCV* getModule(int _id);
    int countModule() const;
    bool hasModule() const;
    bool hasModule(int _id);
    //
    void onRunOpenCV(GObject* _request, GSocket* _client);
    static DWORD WINAPI onRunOpenCVThread(LPVOID _params);
    void onClearWindowId(GObject* _request, GSocket* _client);
    void onOpenImageFile(GObject* _request, GSocket* _client);
    void onUnknownMethod(GObject* _request, GSocket* _client);

private:
    static GOpenCV* m_instance;
    //
    cv::Mat m_img;
    std::string m_winname;
    //
    static int m_winnameId;
    static std::map<int, GOpenCV*> m_opencvMap;
};
//==============================================
#endif
//==============================================
