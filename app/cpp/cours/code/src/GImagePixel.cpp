//===============================================
#include "GImagePixel.h"
#include "GManager.h"
//===============================================
GImagePixel::GImagePixel(QObject* parent) : GOpenCVUi(parent) {

}
//===============================================
GImagePixel::~GImagePixel() {

}
//===============================================
void GImagePixel::run(int argc, char** argv) {
    sGApp* lApp = GManager::Instance()->getData()->app;

    cv::Mat img_rgb, img_gry;

    img_rgb = cv::imread( lApp->opencv_image_file );
    cv::cvtColor( img_rgb, img_gry, cv::COLOR_BGR2GRAY);

    int x = 16, y = 32;
    cv::Vec3b intensity = img_rgb.at< cv::Vec3b >(y, x);

    uchar blue = intensity[0];
    uchar green = intensity[1];
    uchar red = intensity[2];

    std::cout << "At (x,y) = (" << x << ", " << y <<
    "): (blue, green, red) = (" <<
    (unsigned int)blue << ", " <<
	(unsigned int)green << ", " <<
    (unsigned int)red << ")" << std::endl;

    std::cout << "Gray pixel there is: " <<
    (unsigned int)img_gry.at<uchar>(y, x) << std::endl;

    img_gry.at<uchar>(x, y) = 128;

    intensity[0] = 128;
    intensity[1] = 128;
    intensity[2] = 128;

    img_rgb.at< cv::Vec3b >(y, x) = intensity;
}
//===============================================
