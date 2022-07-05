//===============================================
#ifndef _GTitleBar_
#define _GTitleBar_
//===============================================
#include "GWidget.h"
//===============================================
class GTitleBar : public GWidget {
    Q_OBJECT

public:
    GTitleBar(QWidget* _parent = 0);
    ~GTitleBar();
    void createLayout();
    void addObj(const QString& _key, void* _obj);
    void* getObj(const QString& _key, void* _defaultValue = 0) const;
    QString getKey(void* _obj, const QString& _defaultValue = "") const;
    void onClose();
    void onMinimize();
    void onMaximize();
    void onFullscreen();

public slots:
    void onEvent();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    QWidget* m_mainWindow;
    QMap<QString, void*> m_objs;
    QPoint m_pressPos;
    bool m_pressFlag;
};
//===============================================
#endif
//===============================================
