//===============================================
#ifndef _GHelloGLLogo_
#define _GHelloGLLogo_
//===============================================
#include "GInclude.h"
//===============================================
class GHelloGLLogo : public QObject {
    Q_OBJECT

public:
    GHelloGLLogo(QObject* parent = 0);
    virtual ~GHelloGLLogo();
    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

private:
    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4);
    void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    void add(const QVector3D &v, const QVector3D &n);

private:
    QVector<GLfloat> m_data;
    int m_count = 0;
};
//==============================================
#endif
//==============================================
