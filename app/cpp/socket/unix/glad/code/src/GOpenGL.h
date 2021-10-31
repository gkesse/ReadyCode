//===============================================
#ifndef _GOpenGL_
#define _GOpenGL_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenGL {
public:
	GOpenGL();
	~GOpenGL();
	void init(int _major, int _minor, int _samples);
	void heatMap(float _v, float _vmin, float _vmax, float& _r, float& _g, float& _b);

private:
	GLFWwindow* m_window;
	std::string m_title;
	int m_width;
	int m_height;
};
//==============================================
#endif
//==============================================
