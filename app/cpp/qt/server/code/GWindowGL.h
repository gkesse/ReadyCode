//================================================
#ifndef _GWindowGL_
#define _GWindowGL_
//================================================
#include <QtWidgets>
#include <QOpenGLWindow>
//================================================
class GWindowGL : public QOpenGLWindow {
    Q_OBJECT
    
public:
    GWindowGL();
    ~GWindowGL();

protected:
	void initializeGL();
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
    
private:
	QOpenGLContext* m_context;
    QOpenGLVertexArrayObject* m_vao;
    QOpenGLShaderProgram* m_shaderProgram;
};
//================================================
#endif
//================================================