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
	unsigned int loadShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
	unsigned int loadShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	unsigned int loadTexture(const std::string& textureFile);
	void setBool(unsigned int programId, const std::string &name, bool value);
	void setInt(unsigned int programId, const std::string &name, int value);
	void setFloat(unsigned int programId, const std::string &name, float value);

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
	// shader
	std::string shader_vertex_file;
	std::string shader_fragment_file;
	// texture
	std::string texture_file;
};
//==============================================
#endif
//==============================================
