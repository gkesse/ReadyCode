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
	bool isClose();
	void close();
	void pollEvents();
	void bgcolor(const sGColor& _color);
	void bgcolor2(const sGColor& _color);
	sGColor heatMap(float _v, float _vmin, float _vmax, const sGColor& _color);
	void info();
	void extensions();
	void debug();
	void debug2();
	static void APIENTRY onDebug(GLenum source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _msg, const void* _param);

private:
	GLFWwindow* m_window;
	std::string m_title;
	int m_width;
	int m_height;
};
//==============================================
#endif
//==============================================
