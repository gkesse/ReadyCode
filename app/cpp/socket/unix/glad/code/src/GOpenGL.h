//===============================================
#ifndef _GOpenGL_
#define _GOpenGL_
//===============================================
#include "GInclude.h"
#include "GStruct.h"
#include "GFunction.h"
//===============================================
class GOpenGL {
public:
	GOpenGL();
	~GOpenGL();
	void init(int _major, int _minor, int _samples);
	sGColor heatMap(float _v, float _vmin, float _vmax, const sGColor& _color);

private:
	GLFWwindow* m_window;
	std::string m_title;
	int m_width;
	int m_height;
};
//==============================================
#endif
//==============================================
