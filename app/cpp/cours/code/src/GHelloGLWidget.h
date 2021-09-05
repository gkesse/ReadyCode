//===============================================
#ifndef _GHelloGLWidegt_
#define _GHelloGLWidegt_
//===============================================
#include "GInclude.h"
#include "GHelloGLLogo.h"
//===============================================
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
//===============================================
class GHelloGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    GHelloGLWidget(QWidget* parent = 0);
    virtual ~GHelloGLWidget();

    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    static void qNormalizeAngle(int &angle);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

private:
    void setupVertexAttribs();

private:
    bool m_core;
    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
    QPoint m_lastPos;
    GHelloGLLogo m_logo;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_logoVbo;
    QOpenGLShaderProgram *m_program = nullptr;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    static bool m_transparent;
};
//==============================================
#endif
//==============================================
