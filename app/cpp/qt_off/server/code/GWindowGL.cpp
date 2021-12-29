//================================================
#include "GWindowGL.h"
//================================================
GWindowGL::GWindowGL() : QOpenGLWindow() {
	setSurfaceType(QWindow::OpenGLSurface);

	QSurfaceFormat lFormat;
	lFormat.setProfile(QSurfaceFormat::CoreProfile);
	lFormat.setVersion(3, 2);
	setFormat(lFormat);

	QOpenGLContext* lContext = new QOpenGLContext();
    m_context = lContext;
	lContext->setFormat(lFormat);
	lContext->create();
	lContext->makeCurrent(this);
}
//================================================
GWindowGL::~GWindowGL() {

}
//================================================
void GWindowGL::initializeGL() {
	static const char* lVertexShader =
	"#version 330 core\n"
	"layout(location = 0) in vec2 posAttr;\n"
	"void main() {\n"
	"gl_Position = vec4(posAttr, 0.0, 1.0);\n"
    "}";

	static const char* lFragmentShader =
	"#version 330 core\n"
	"out vec4 col;\n"
	"void main() {\n"
	"col = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}";

	QOpenGLShaderProgram* lShaderProgram = new QOpenGLShaderProgram(this);
	m_shaderProgram = lShaderProgram;
    lShaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, lVertexShader);
	lShaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, lFragmentShader);
	lShaderProgram->link();

	GLfloat lVertices[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		0.0f,  1.0f
	};

	QOpenGLVertexArrayObject* lVao = new QOpenGLVertexArrayObject();
	m_vao = lVao;
    lVao->create();
	lVao->bind();

	QOpenGLBuffer* lVbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	lVbo->create();
	lVbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
	lVbo->bind();
	lVbo->allocate(lVertices, sizeof(lVertices) * sizeof(GLfloat));

	lVao->release();
}
//================================================
void GWindowGL::paintEvent(QPaintEvent *event) {
    const qreal lRatio = devicePixelRatio();
    glViewport(0, 0, width() * lRatio, height() * lRatio);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_vao->bind();
	m_shaderProgram->bind();

	m_shaderProgram->bindAttributeLocation("posAttr", 0);
	m_shaderProgram->enableAttributeArray(0);
	m_shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 2);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	m_shaderProgram->release();
	m_vao->release();
}
//================================================
void GWindowGL::resizeEvent(QResizeEvent *event) {
	glViewport(0, 0, width(), height());
	update();
}
//================================================
