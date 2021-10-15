//===============================================
#ifndef _GOpenCV_
#define _GOpenCV_
//===============================================
#include "GInclude.h"
//===============================================
class GOpenCV {
public:
	GOpenCV();
	~GOpenCV();
	void filename(const std::string _filename);
	void title(const std::string _title);
	void showImage();

private:
	std::string m_filename;
	std::string m_title;
};
//==============================================
#endif
//==============================================
